
#include "net_ipv6.h"

int f_ipv6(const u_char* packet, int* size){
    int i;
    char str[INET6_ADDRSTRLEN];
    struct ipv6hdr* ip6head=(struct ipv6hdr*)(packet+*size);

    *size+=sizeof(struct ipv6hdr);

    V_printf(1,"  IPv6     ");

    if(verbosity_user==3) V_printf(3,"\n");
    else V_printf(1,"  ->  ");             //set the display according to verbosity

    V_printf(3,"\033[33m\n");   //set the color

    inet_ntop(AF_INET6, &(ip6head->ipv6_src), str, INET6_ADDRSTRLEN);
    V_printf(2,"    Source : %ss", str);

    if(verbosity_user==3) V_printf(3,"\n");
    else V_printf(2,"  ->  ");

    inet_ntop(AF_INET6, &(ip6head->ipv6_dst), str, INET6_ADDRSTRLEN);
    V_printf(2,"    Destination : %s\n", str);
    V_printf(3,"    Next header : ");
    switch(ip6head->ipv6_nextheader){
        case NEXTHDR_TCP :
            V_printf(3,"TCP segment");
        break;
        case NEXTHDR_UDP :
            V_printf(3,"UDP message");
        break;
        case NEXTHDR_IPV6:
            V_printf(3,"IPv6 in IPv6");
        break;
        case NEXTHDR_ICMP:
            V_printf(3,"ICMP for IPv6");
        break;
    }
    V_printf(3," (%u)\n", ip6head->ipv6_nextheader);
    V_printf(3,"    Flow label : 0x");
    for(i=0;i<3;i++)
        V_printf(3,"%.2x",ip6head->ipv6_flow_lbl[i]);
    V_printf(3,"\n");
    V_printf(3,"    Payload length : %u\n", ntohs(ip6head->ipv6_len));
    V_printf(3,"    Hop limit : %u\n", ip6head->ipv6_hoplimit);

    printf("\033[00m");  //adjust the color to default
    printf("\n");
    return(0);
}
