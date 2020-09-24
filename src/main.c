#include <stdio.h>
#include <unistd.h>

#include "parser.c"

// Initializing of main variables //
  lex_state state;
  lex_token token;




//-------------------------------------/
int main(){

  int error_flag = parser();
  if(error_flag==0){
    printf("File parsed sucessfully\n");
  }
  else{

    printf("Parsing failed with error %d\n", error_flag);
    return(-1);
  }


  while(1){

     token = get_token();
     if(token.value == -1){
       printf("end of file\n");
       return(0);
     }
     printf("%c",token.value);


  }


}
