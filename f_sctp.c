
#include "sctp.h"
//SCTP FLAGS
#define IS_DATA     0x00
#define IS_INIT     0x01
#define IS_INITA    0x02
#define IS_SACK     0x03
#define IS_HB       0x04
#define IS_HBA      0x05
#define IS_ABORT    0x06
#define IS_SHUT     0x07
#define IS_SHUTA    0x08
#define IS_ERR      0x09


int f_sctp(const u_char* packet, int* size) {
    struct sctphdr* sctphead=(struct sctphdr*)(packet+*size);
    *size+=sizeof(struct sctphdr);
    //header_size = 4 * tcphead->th_off;
    V_printf(1,"  SCTP     ");

    if(verbosity_user==3) V_printf(3,"\n");   //set the display according to verbosity
    else V_printf(1,"  ->  ");

    V_printf(3,"\033[36m");  //set the color

    V_printf(2,"       Source port : %d", ntohs(sctphead->src_port));

    if(verbosity_user==3) V_printf(3,"\n");      //set the display according to verbosity
    else if(verbosity_user==2) V_printf(1,"  ->  ");

    V_printf(2,"        Destination port : %d\n", ntohs(sctphead->dest_port));
    V_printf(3,"        Verification tag of packet : 0x%2x\n", ntohl(sctphead->v_tag));
    V_printf(3,"        SCTP checksum : 0x%2x\n", ntohl(sctphead->checksum));
    V_printf(3,"        DATA chunk:\n");

    struct sctp_chunkhdr* sctphead2=(struct sctp_chunkhdr*)(packet+*size);
    *size+=sizeof(struct sctp_chunkhdr);

    V_printf(3,"            Chunk type : ");
    switch(ntohs(sctphead2->chunk_type)){
        case IS_DATA:
            V_printf(3,"Payload Data (DATA)");
            break;
        case IS_INIT:
            V_printf(3,"Initiation (INIT)");
            break;
        case IS_INITA:
            V_printf(3,"Initiation Acknowledgment (INIT ACK)");
            break;
        case IS_SACK:
            V_printf(3,"Selective Acknowledgment (SACK)");
            break;
        case IS_HB:
            V_printf(3,"Hearbeat Request (HEARTBEAT)");
            break;
        case IS_HBA:
            V_printf(3,"Hearbeat Acknowledgment (HEARTBEAT ACK)");
            break;
        case IS_ABORT:
            V_printf(3,"Abort (ABORT)");
            break;
        case IS_SHUT:
            V_printf(3,"Shutdown (SHUTDOWN)");
            break;
        case IS_SHUTA:
            V_printf(3,"Shutdown Acknowledgment (SHUTDOWN ACK)");
            break;
        case IS_ERR:
            V_printf(3,"Operation Error (ERROR)");
            break;
    }
    V_printf(3," (%i)\n", ntohs(sctphead2->chunk_type));
    V_printf(3,"            Chunk flags : 0x%x\n", ntohs(sctphead2->chunk_flags));
    V_printf(3,"            Chunk length : %i\n", ntohs(sctphead2->chunk_length));
    printf("\n");

    printf("\033[00m"); //adjust the color to default
    return(0);
}
