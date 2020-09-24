#include "scanner.c"
#include <stdbool.h>

int parser(){

  lex_token token;
  bool pars_flag = 0;

  while(1){

     token = get_token();
     if(token.value == -1){

       if(pars_flag == 1){
         printf("Syntactic error\n");
         return(-1);
       }
        return(0);
      }


     if(token.value == 34){
       pars_flag = !pars_flag;
     }



  }



return(0);
}
