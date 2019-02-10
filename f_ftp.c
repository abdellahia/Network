

void f_ftp(const u_char* packet, int* size, int* size_c){

        V_printf(1,"  FTP ");
        V_printf(3,"\033[36m\n"); //set the color
        ascii(packet,size,*size_c);
        V_printf(3,"\033[0m\n"); //adujst the color to defalut
  		printf("\n");

}
