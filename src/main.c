#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Include user defined files //


#include "parser.h"



int main(int argc, char** argv){
  int error = 0;
 // error = parser_debug();
  tToken j;
  while (j.type!= t_eof)
  {
    j=get_token();
    printf("%d  %s\n",(j.type),(j.value)->str);    
  }
return error;
}



//int scanner_debug(int argc, char **argv)){
  
  
//  return 0;
//}


/*int parser_debug(){












  return parser();
}
*/