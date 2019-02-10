#include <stdio.h>
#include <stdarg.h>

extern int verbosity_user;


/* determines the dispaly methode
    of printf depending
    on verbosity level
*/
void V_printf(int verbosity_program,char *str, ...){
  if(verbosity_user >= verbosity_program){
	  va_list ap;
      va_start(ap, str);
	  vfprintf(stdout, str, ap);
      va_end(ap);
  }
}

/* determines the dispaly methode
    of putchar depending
    on verbosity level
*/

void V_putchar(int verbosity_program,int c){
  if(verbosity_user >= verbosity_program){
	  putchar(c);
  }
}
