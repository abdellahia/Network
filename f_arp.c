#include <netinet/if_ether.h>

#define ARP_MAC_LENGTH				  6
#define ARP_IPv4_LENGTH				  4

#include "projet0.h"

int f_arp(const u_char* packet, int* size){
    int i;

    struct arphdr* arphead=(struct arphdr*)(packet+*size);
    struct ether_arp* arphead2=(struct ether_arp*)(packet+*size);

    *size+=sizeof(struct ether_arp);

    V_printf(1,"  ARP      ");

    if(verbosity_user==2) V_printf(1,"  ->  ");             //set the display
    else if(verbosity_user==3) V_printf(1,"\n\n");          // according to verbosity

    V_printf(3,"\033[36m"); // set the color for verbosity=3

    V_printf(2,"    Hardware type: (%d) ",ntohs(arphead2->arp_hrd));
    switch(ntohs(arphead2->arp_hrd)){
        case ARPHRD_ETHER:
            V_printf(2,"Ethernet");
            break;
        /*case ARPHRD_FRELAY:
            printf("Frame relay\n");
        break;*/
    }
    if(verbosity_user==3) V_printf(3,"\n");
    else if(verbosity_user==2) V_printf(1,"  ->  ");
    V_printf(2,"    Protocol type: (0x%u) ",arphead2->arp_pro);
    switch(ntohs(arphead2->arp_pro)){
        case ETHERTYPE_PUP:
            V_printf(2,"Xerox POP\n");
            break;
        case ETHERTYPE_IP:
            V_printf(2,"IPv4\n");
            break;
        case ETHERTYPE_ARP:
            V_printf(2,"Address resolution \n");
            break;
        case ETHERTYPE_REVARP:
            V_printf(2,"Reserve ARP\n");
            break;
        default:
            V_printf(2,"Unknown\n");
            break;
    }
    V_printf(3,"    Hardware size: %u\n", arphead2->arp_hln);
    V_printf(3,"    Protocol size: %u\n", arphead2->arp_pln);
    V_printf(3,"    Opcode: ");
    /*if(ntohs(arphead2->arp_op)>=1 && ntohs(arphead2->arp_op)<=9 ){
        printf("(%s)\n", op[ntohs(arphead2->arp_op)]);
    }
    else{
        printf("(Undefined)\n");
    }*/
    switch(ntohs(arphead2->arp_op)){
        case ARPOP_REQUEST:
            V_printf(3,"Request (1)\n");
        break;
        case ARPOP_REPLY:
            V_printf(3,"Reply (2)\n");
        break;
    }

    V_printf(3,"    Sender MAC address : ");
    for(i=0;i<ARP_MAC_LENGTH;i++){
        if(i!=0)
            V_printf(3,":");
        V_printf(3,"%.2x",arphead2->arp_sha[i]);
    }
    V_printf(3,"\n");
    V_printf(3,"    Sender IP address : ");
    for(i=0;i<ARP_IPv4_LENGTH;i++){
        if(i!=0)
            V_printf(3,".");
        V_printf(3,"%u",arphead2->arp_spa[i]);
    }
    V_printf(3,"\n");
    V_printf(3,"    Target MAC address : ");
    for(i=0;i<ARP_MAC_LENGTH;i++){
        if(i!=0)
            V_printf(3,":");
        V_printf(3,"%.2x",arphead2->arp_tha[i]);
    }
    V_printf(3,"\n");
    V_printf(3,"    Target IP address : ");
    for(i=0;i<ARP_IPv4_LENGTH;i++){
        if(i!=0)
            V_printf(3,".");
        V_printf(3,"%u",arphead2->arp_tpa[i]);
    }
    printf("\n\n");
    printf("\033[00m");
    return(0);

}


