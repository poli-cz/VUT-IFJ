#include <stdio.h>
#include <unistd.h>
#include "scanner.c"

// Initializing of main variables //
  lex_state state;
  lex_token token;



//-------------------------------------/
int main(){

  while(1){
     token = get_token();
     if(token.value == -1){
       printf("end of file\n");
       return(0);
     }
     printf("%c",token.value);


  }


}
