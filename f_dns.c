
#include "net_sock_dns.h"

//DNS Flags
#define IS_QR        ((ntohs(dnshead->flags) << 1) & 1)
#define IS_OPCODE  ((ntohs(dnshead->flags) << 11) & 15)
#define IS_A        ((ntohs(dnshead->flags) >> 10) & 1)
#define IS_TC        ((ntohs(dnshead->flags) << 9) & 1)
#define IS_RD        ((ntohs(dnshead->flags) >> 8) & 1)
#define IS_RA        ((ntohs(dnshead->flags) << 7) & 1)
#define IS_ZR        ((ntohs(dnshead->flags) << 6) & 1)
#define IS_AA        ((ntohs(dnshead->flags) << 5) & 1)
#define IS_NAD       ((ntohs(dnshead->flags) << 4) & 1)



void f_dns(const u_char* packet, int* size){

    struct sock_dns_hdr_t* dnshead=(struct sock_dns_hdr_t*)(packet+*size);

    *size+=sizeof(struct sock_dns_hdr_t);

    V_printf(1,"  DNS      ");

    if(verbosity_user==3) V_printf(3,"\n");  //set the display according to verbosity
    else V_printf(1,"  ->  ");

    V_printf(3,"\033[36m\n");  //set the color

    V_printf(2,"            Transaction ID : 0x%4.x\n", ntohs(dnshead->id));
    V_printf(3,"            Flags : (0x%.4x) \n",ntohs(dnshead->flags));
    if(!IS_QR)
        V_printf(3,"                =Response: Message is a response\n");
    if(IS_QR)
        V_printf(3,"                =Response: Message is a querry\n");
    if(!IS_OPCODE)
        V_printf(3,"                =Opcode: Standard query (0)\n");
    if(IS_A)
        V_printf(3,"                =Authorative: Server is an authority for domain\n");
    if(!IS_TC)
        V_printf(3,"                =Truncated: Message is not truncated\n");
    if(IS_RD)
        V_printf(3,"                =Recursion desired: Do query recursively\n");
    if(!IS_RA)
        V_printf(3,"                =Recursion available: Server can do recursive queries\n");
    if(!IS_ZR)
        V_printf(3,"                =Z: reserved (0)\n");
    if(!IS_AA)
        V_printf(3,"                =Answer authenticated: Answer/authority protion was not\n");
        V_printf(3,"                            authenticated by the server\n");
    if(!IS_NAD)
        V_printf(3,"                =Non-authenticated data: Unacceptable\n");
    V_printf(3,"            Questions : %i\n",ntohs(dnshead->qdcount));
    V_printf(3,"            Answer RRs : %i\n",ntohs(dnshead->ancount));
    V_printf(3,"            Authority RRs : %i\n",ntohs(dnshead->nscount));
    V_printf(3,"            Additional RRs : %i\n",ntohs(dnshead->arcount));
    printf("\n");

    V_printf(3,"\033[00m");  //set the color to deflaut

}

