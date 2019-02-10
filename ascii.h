#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NULLCHAR        0x00  //Character null
#define END_OF_ASCII    0x1F  // limit of ascii table
#define R               0x0d  // \r
#define N               0x0a // \,

// fonction that converts ascii
void ascii(const u_char* packet, int* size, int size_c) {

    if(size_c!=0) {
        int i = 1;
        char pack=packet[*size];
        V_printf(3,"\n           ");
        while(pack!= NULLCHAR && i<=size_c){
            pack=packet[*size];
            if(pack==R && packet[(*size)+1]==R) {
                    V_printf(3,"\n           ");
                    *size+=1;
            }
            else if(pack==N) V_printf(3,"\n           ");
            else if(pack<=END_OF_ASCII && pack!=R && pack!=N && pack!=NULLCHAR) V_printf(3,".");
            else V_printf(3,"%c",pack);
            *size+=1;
            i++;
        }
        *size+=1;
    }
}
