#include "bootp.h"


#define IS_BROADCAST                       0x8000
#define IS_U            ((ntohs(bootphead->bp_flags) << 1) & 1)


void f_bootp(const u_char* packet, int* size){
    int i;

    struct bootp* bootphead=(struct bootp*)(packet+*size);

    *size+=sizeof(struct bootp);

    V_printf(1,"  BOOTP    ");

    if(verbosity_user==3) V_printf(3,"\n");  //set the display according to verbosity
    else V_printf(1,"  ->  ");


    V_printf(3,"\033[35m \n");  //set the color
    V_printf(2,"            Packet opcode type : (%i) ", bootphead->bp_op);
    switch(bootphead->bp_op){
        case BOOTREQUEST:
        V_printf(2,"Request\n");
        break;
        case BOOTREPLY:
        V_printf(2,"Reply\n");
        break;
    }
    V_printf(3,"            Hardware addr type : (0x%.2x) ", bootphead->bp_htype);
    switch(bootphead->bp_htype){
        case HTYPE_ETHERNET:
            V_printf(3,"Ethernet\n");
        break;
        case HTYPE_EXP_ETHERNET:
            V_printf(3,"Experimental Ethernet\n");
        break;
        case HTYPE_AX25:
            V_printf(3,"Radio amateur AX25\n");
        break;
        case HTYPE_PRONET:
            V_printf(3,"Proteon ProNET Token Ring\n");
        break;
        case HTYPE_CHAOS:
            V_printf(3,"Chaos\n");
        break;
        case HTYPE_IEEE802:
            V_printf(3,"IEEE 802\n");
        break;
        case HTYPE_ARCNET:
            V_printf(3,"Arcnet\n");
        break;
        default:
            V_printf(3,"Others\n");
        break;
    }
    V_printf(3,"            Hardware addr length : %i \n", bootphead->bp_hlen);
    V_printf(3,"            Gateway hops : %i\n", bootphead->bp_hops);
    V_printf(3,"            Transaction ID : 0x%.8x\n", ntohl(bootphead->bp_xid));
    V_printf(3,"            Seconds elapsed : %i s\n", ntohs(bootphead->bp_secs));
    V_printf(3,"            Bootp flags : (0x%.4x) ",ntohs(bootphead->bp_flags) );
    if(IS_U) V_printf(3," Unicast\n");
    else V_printf(3," Reserved\n");
    /*switch(ntohs(bootphead->bp_flags)){
        case IS_U:
            printf("(Unicast)\n");
        break;
        default:
            printf("Reserved\n");
    }*/
    V_printf(3,"            Client IP address : %s\n", inet_ntoa(bootphead->bp_ciaddr));
    V_printf(3,"            'Your' IP address : %s\n", inet_ntoa(bootphead->bp_yiaddr));
    V_printf(3,"            Server IP address : %s\n", inet_ntoa(bootphead->bp_siaddr));
    V_printf(3,"            Gateway IP address : %s\n", inet_ntoa(bootphead->bp_giaddr));
    V_printf(3,"            Client MAC address : ");
    for(i=0;i<6;i++){
        V_printf(3,"%.2x:",bootphead->bp_chaddr[i]);
    }
    V_printf(3,"\n            Client hardware address padding: ");
    for(i=6;i<16;i++){
        V_printf(3,"%.2x:",bootphead->bp_chaddr[i]);
    }
    V_printf(3,"\n");
    if(bootphead->bp_file[0] != '\0')
        V_printf(3," | File %s", bootphead->bp_file);
    V_printf(3,"            Server host name : ");
    if(bootphead->bp_sname[0]==0)
        V_printf(3,"not given\n");
    else
        V_printf(3,"            %s\n", bootphead->bp_sname);
    V_printf(3,"            Boot file name : ");
    if(bootphead->bp_file[0]==0)
        V_printf(3,"not given\n");
    else
        V_printf(3,"%s\n", bootphead->bp_file);


    //bootp options
    u_int8_t *pvendor = bootphead->bp_vend;
    const u_int8_t magic_cookie[] = VM_RFC1048;

    if(memcmp(pvendor, magic_cookie, 4) == 0) {
        pvendor += 4;
        V_printf(3,"                | Magic cookie 0x%02x%02x%02x%02x\n", pvendor[0], pvendor[1], pvendor[2], pvendor[3]);

        int comp_option=0;
        while(comp_option<10) {
            u_int8_t option=0;
            u_int8_t len;
            option = *pvendor++;
            len = *pvendor++;

            if(option != 0) V_printf(3,"                | Option %u : ", option);

            switch (option) {
                case TAG_PAD:
                    break;
                case TAG_SUBNET_MASK:
                    V_printf(3,"Subnet mask: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_GATEWAY:
                    V_printf(3,"Gateway: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_TIME_SERVER:
                    V_printf(3,"Time server: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_DOMAIN_SERVER:
                    V_printf(3,"Domain name server: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_HOSTNAME:
                    V_printf(3,"Host name: ");
                    for(i = 0; i < len; i++) V_putchar(3,pvendor[i]);
                    break;
                case TAG_DOMAINNAME:
                    V_printf(3,"Domain name: ");
                    for(i = 0; i < len; i++) V_putchar(3,pvendor[i]);
                    break;
                case TAG_END:
                    V_printf(3,"End of options\n");
                    return;
                case TAG_BROAD_ADDR:
                    V_printf(3,"Broadcast address: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_REQUESTED_IP:
                    V_printf(3,"Requested IP: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_IP_LEASE:
                    V_printf(3,"IP lease time: %us", ntohl(*(u_int32_t *)pvendor));
                    break;
                case TAG_DHCP_MESSAGE: {
                    u_int8_t dhcp_message = *pvendor;
                    switch (dhcp_message) {
                        case DHCPDISCOVER:
                            V_printf(3,"DHCP Discover");
                            break;
                        case DHCPOFFER:
                            V_printf(3,"DHCP Offer");
                            break;
                        case DHCPREQUEST:
                            V_printf(3,"DHCP Request");
                            break;
                        case DHCPDECLINE:
                            V_printf(3,"DHCP Decline");
                            break;
                        case DHCPACK:
                            V_printf(3,"DHCP Ack");
                            break;
                        case DHCPNAK:
                            V_printf(3,"DHCP N-Ack");
                            break;
                        case DHCPRELEASE:
                            V_printf(3,"DHCP Release");
                            break;
                        case DHCPINFORM:
                            V_printf(3,"DHCP Inform");
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case TAG_SERVER_ID:
                    V_printf(3,"DHCP server identifier: "); V_printf(3,"%u",ntohl(*(int32_t *)pvendor));
                    break;
                case TAG_PARM_REQUEST:
                    V_printf(3,"Parameter request list");
                    break;
                case TAG_RENEWAL_TIME:
                    V_printf(3,"Renewal time: %us", ntohl(*(u_int32_t*)pvendor));
                    break;
                case TAG_REBIND_TIME:
                    V_printf(3,"Rebinding time: %us", ntohl(*(u_int32_t*)pvendor));
                    break;
                case TAG_CLIENT_ID:
                    V_printf(3,"Client identifier: "); printf("%s",pvendor + 1);
                    break;
                case TAG_MAX_MSG_SIZE:
                    V_printf(3,"Maximue DHCP Message Size");
                    break;
                case TAG_OPT_OVERLOAD:
                    V_printf(3,"Option Overload"); //a rectifier
                    break;
                default:
                    break;
            }

            if(option != 0) putchar('\n');
            pvendor += len;
            comp_option++;
        }
    }
    printf("\n");
    printf("\033[00m");

}
