
#define NOFRAG 0x4000
#define MOREFRAG 0x2000



int f_ip(const u_char* packet, int* size, int* size_c){

    struct ip* iphead=(struct ip*)(packet+*size);
    int pro;

    *size_c=iphead->ip_hl*4;
    *size+=*size_c; //size of protocol
    *size_c=ntohs(iphead->ip_len)-*size_c; //size of data

    V_printf(1,"  IPv4     ");

    if(verbosity_user==3) V_printf(3,"\n");
    else V_printf(1,"  ->  ");

    V_printf(3,"    \033[33m\n");  //set the color

    V_printf(2,"    IP source : %s", inet_ntoa(iphead->ip_src));

    if(verbosity_user==3) V_printf(3,"\n");             //set the display according with verbosity
    else if(verbosity_user==2) V_printf(1,"  ->  ");

    V_printf(2,"    IP destination : %s\n", inet_ntoa(iphead->ip_dst));
    V_printf(3,"    Header length : %i bytes\n", (iphead->ip_hl)*4);
    V_printf(3,"    Type of Service : 0x%.2x\n", iphead->ip_tos);
    V_printf(3,"    Total lenght : %i octets\n", ntohs(iphead->ip_len));
    V_printf(3,"    Identification : 0x%.4x\n", ntohs(iphead->ip_id));
    V_printf(3,"    Fragment offset field : 0x%.4x", ntohs(iphead->ip_off));
    switch(ntohs(iphead->ip_off)){
        case NOFRAG:
            V_printf(3,"    (Dont't fagment flag)\n");
            break;
        case MOREFRAG:
            V_printf(1,"    (More fragments flag)\n");
            break;
        default:
            V_printf(3,"\n");
            break;
    }
    V_printf(3,"    Time to live : %i\n", iphead->ip_ttl);
    switch(iphead->ip_p){
        case IS_TCP:
            V_printf(3,"    Protocol : TCP");
            pro=IS_TCP;
            break;
        case IS_UDP:
            V_printf(3,"    Protocol : UDP");
            pro=IS_UDP;
            break;
        case IS_ICMP:
            V_printf(3,"    Protocol : ICMP");
            pro=IS_ICMP;
            break;
        case IS_SCTP:
            V_printf(3,"    Protocol : SCTP");
            pro=IS_SCTP;
            break;
        default:
            V_printf(3,"\n");
            break;
    }
    V_printf(3," (%i)\n", iphead->ip_p);
    V_printf(3,"    Checksum : 0x%.4x\n\n", ntohs(iphead->ip_sum));
    V_printf(3,"\033[00m");

    switch(pro){
        case IS_TCP:
            return IS_TCP;
        case IS_UDP:
            return IS_UDP;
        case IS_ICMP:
            return IS_ICMP;
        case IS_SCTP:
            return IS_SCTP;
    }

    V_printf(3,"\033[00m"); //adjust the color to ddefault

    return(0);
}



