

void f_tcp(const u_char* packet, int* size, int* size_c) {

    struct tcphdr* tcphead = (struct tcphdr*)( packet + *size);
    int tcp_len=sizeof(tcphead);
    int data_offset=4 * tcphead->th_off;
    *size+= 4 * tcphead->th_off;  //protocol size
    *size_c-= 4 * tcphead->th_off; //data size

    V_printf(1,"  TCP      ");
    if(verbosity_user==3) V_printf(3,"\n");
    else V_printf(1,"  ->  ");         //set the display according to verbosity

    V_printf(3,"\033[35m"); //set the color

    V_printf(2,"        Source port : %i", ntohs(tcphead->th_sport));

    if(verbosity_user==3) V_printf(3,"\n");
    else if(verbosity_user==2) V_printf(1,"  ->  ");

    V_printf(2,"        Destination port : %i\n", ntohs(tcphead->th_dport));
    V_printf(3,"        Sequence number : 0x%.4x\n", ntohs(tcphead->th_seq));
    V_printf(3,"        Acknowledgment number : 0x%.4x\n", ntohs(tcphead->th_ack));
    V_printf(3,"        Sequence number : 0x%.4x\n", ntohs(tcphead->th_seq));
    V_printf(3,"        Data offset : %i bytes\n", tcphead->th_off*4);
    V_printf(3,"        Unused : %i\n", tcphead->th_x2*4);
    V_printf(3,"        Flags : (0x%.4x)", tcphead->th_flags);
    switch(tcphead->th_flags){
        case TH_FIN:
        V_printf(3," FIN\n");
        break;
        case TH_SYN:
        V_printf(3," SYN\n");
        break;
        case TH_RST:
        V_printf(3," RST\n");
        break;
        case TH_PUSH:
        V_printf(3," PSH\n");
        break;
        case TH_ACK:
        V_printf(3," ACK\n");
        break;
        case TH_URG:
        V_printf(3," URG\n");
        break;
    }
    V_printf(3,"        Window : %i\n", ntohs(tcphead->th_win));
    V_printf(3,"        Checksum : 0x%.4x\n", ntohs(tcphead->th_sum));
    V_printf(3,"        Urgent pointer : %i\n", ntohs(tcphead->th_urp));

    V_printf(3,"\033[00m"); //adjust the color to defauly

    printf("\n");

    if(*size_c!=0 ){
        //HTTP
        if((ntohs(tcphead->th_sport)==IS_HTTP
            || ntohs(tcphead->th_dport)==IS_HTTP))
        {
            f_http(packet,size,size_c);
        }
        //SMTP
        if((ntohs(tcphead->th_sport)==IS_SMTP
            || ntohs(tcphead->th_dport)==IS_SMTP))
        {
            f_smtp(packet,size,size_c);
        }
        //TELNET
        if((ntohs(tcphead->th_sport)==IS_TELNET
            || ntohs(tcphead->th_dport)==IS_TELNET))
        {
            f_telnet(packet,*size,*size_c);
        }
        //FTP
        if((ntohs(tcphead->th_sport)==IS_FTP
            || ntohs(tcphead->th_dport)==IS_FTP))
        {
            f_ftp(packet,size,size_c);
        }
        //POP
        if((ntohs(tcphead->th_sport)==IS_POP
            || ntohs(tcphead->th_dport)==IS_POP))
        {
            f_pop(packet,size,size_c);
        }
        //IMAP
        if((ntohs(tcphead->th_sport)==IS_IMAP
            || ntohs(tcphead->th_dport)==IS_IMAP))
        {
            f_imap(packet,size,size_c);
        }
    }
}

