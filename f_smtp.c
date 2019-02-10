#include "projet0.h"


void f_smtp(const u_char* packet, int* size, int* size_c){

    V_printf(1,"  SMTP ");
    V_printf(3,"\033[36m");  //set the color
    ascii(packet,size,*size_c);
    V_printf(3,"\033[00m");  //adujst the color to default
    printf("\n");

}
