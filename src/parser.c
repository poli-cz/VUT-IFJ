#include "scanner.c"
#include <stdbool.h>

int parser(){

  lex_token token;
  //bool pars_flag = 0;

  while(1){

     token = get_token();
     printf("%c", token.value);
     if(token.value==-1){
       return(0);
     }
  }

return(0);
}
