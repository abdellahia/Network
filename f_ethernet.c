#include "projet0.h"

int f_ethernet(const u_char* packet, int* size){
    int i; int pro;

    struct ether_header* ehead = (struct ether_header *) packet;
    *size+=sizeof(struct ether_header);

    V_printf(1,"  ETHERNET ");

    if(verbosity_user==3) V_printf(3,"\n"); //set the display according to verbosity
    else V_printf(1,"  ->  ");

    V_printf(3,"\033[34m\n");  //set the color

    V_printf(2,"  MAC Dest : ");
    for(i=0;i<6;i++){
        V_printf(2,"%.2x:",ehead->ether_dhost[i]);
    }
    if(verbosity_user==3) V_printf(3,"\n");
    else if(verbosity_user==2) V_printf(2,"  ->  ");
    V_printf(2,"  MAC Src : ");
    for(i=0;i<6;i++){
        V_printf(2,"%.2x:",ehead->ether_shost[i]);
    }
    V_printf(2,"\n");
    V_printf(3,"  Type :");
    switch(ntohs(ehead->ether_type)){
        case IS_IP:
            V_printf(3," IPv4");
            pro=IS_IP;
            break;
        case IS_IP6:
            V_printf(3," IPv6");
            pro=IS_IP6;
            break;
        case IS_ARP:
            V_printf(3," ARP");
            pro=IS_ARP;
            break;
    }
    V_printf(3," (0x%.4x)\n",ntohs(ehead->ether_type));
    V_printf(3,"\n\033[00m");
    switch(pro){
        case IS_IP:
            return IS_IP;
        case IS_IP6:
            return IS_IP6;
        case IS_ARP:
            return IS_ARP;
        default :
            return 0;
    }

    V_printf(3,"\033[00m"); //adujst the color to default
    return(0);
}

