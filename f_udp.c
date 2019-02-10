

void f_udp(const u_char* packet, int* size) {
    u_int header_size;
    struct udphdr* udphead=(struct udphdr*)(packet+*size);

    *size+=sizeof(struct udphdr);

    V_printf(1,"  UDP      ");

    if(verbosity_user==3) V_printf(3,"\n");
    else V_printf(1,"  ->  ");       //set the display according to verbosity

    V_printf(3,"\033[36m"); //set the color

    V_printf(2,"        Source port : %d", ntohs(udphead->uh_sport));
    if(verbosity_user==3) V_printf(3,"\n");
    else if(verbosity_user==3) V_printf(2,"  ->  ");

    V_printf(2,"        Destination port : %d\n", ntohs(udphead->uh_dport));
    V_printf(3,"        Udp length : %d\n", ntohs(udphead->uh_ulen));
    V_printf(3,"        Udp checksum : 0x%X\n", ntohs(udphead->uh_sum));
    printf("\n");

    printf("\033[00m");  //adujst the color to default

    //BOOTP
    if((ntohs(udphead->uh_sport)==IS_BOOTP1 && ntohs(udphead->uh_dport)==IS_BOOTP2)
      || (ntohs(udphead->uh_sport)==IS_BOOTP2 && ntohs(udphead->uh_dport)==IS_BOOTP1))
      {
        f_bootp(packet,size);
      }
    //DNS
    if((ntohs(udphead->uh_sport)==IS_DNS || ntohs(udphead->uh_dport)==IS_DNS))
        {
        f_dns(packet,size);
        }


}

