#include "icmp.h"

int f_icmp(const u_char* packet, int* size){
    unsigned short iphdrlen;

    struct ip* iphead = (struct ip *) packet;
    iphdrlen = iphead->ip_hl * 4;
    struct icmphdr *icmph = (struct icmphdr *) (packet +*size);

    *size+=sizeof(struct icmphdr);

    V_printf(1,"  ICMP     ");

    if(verbosity_user==3) V_printf(3,"\n"); //set the display according to verbosity
    else V_printf(1,"  ->  ");

    V_printf(3,"\033[36m"); //set the color

    V_printf(2,"        Type : ");
    switch(icmph->type) {
        case ICMP_ECHOREPLY:
            V_printf(2,"Echo Reply");
            break;
        case ICMP_DEST_UNREACH:
            V_printf(2,"Destination Unreachable");
            break;
        case ICMP_SOURCE_QUENCH:
            V_printf(2,"Source Quench");
            break;
        case ICMP_REDIRECT:
            V_printf(2,"Redirect (change route)");
            break;
        case ICMP_ECHO:
            V_printf(2,"Echo Request");
            break;
        case ICMP_TIME_EXCEEDED:
            V_printf(2,"Time Exceeded");
            break;
        case ICMP_PARAMETERPROB:
            V_printf(2,"Parameter Problem");
            break;
        case ICMP_TIMESTAMP:
            V_printf(2,"Timestamp Request");
            break;
        case ICMP_TIMESTAMPREPLY:
            V_printf(2,"Timestamp Reply");
            break;
        case ICMP_INFO_REQUEST:
            V_printf(2,"Information Request");
            break;
        case ICMP_INFO_REPLY:
            V_printf(2,"/* Information Reply");
            break;
        case ICMP_ADDRESS:
            V_printf(2,"Address Mask Request");
            break;
        case ICMP_ADDRESSREPLY:
            V_printf(2,"Address Mask Reply");
            break;
        default:
            V_printf(2,"Unknown type");
    }

    V_printf(2," (%u)\n", icmph->type);

    V_printf(3,"        Code : %d\n", (unsigned int) (icmph->code));
    V_printf(3,"        Checksum : 0x%.4x\n", ntohs(icmph->checksum));
    V_printf(3,"        Identifier : %d (0x%.4x)\n", ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.id));
    V_printf(3,"        Sequence : %d (0x%.4x)\n", ntohs(icmph->un.echo.sequence), ntohs(icmph->un.echo.sequence));

    printf("\033[00m"); //adujst the color to default
    printf("\n");
    return(0);
}


