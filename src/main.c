#include <stdio.h>
#include <unistd.h>

#include "parser.c"
#include "basic.c"

// Initializing of main variables //

  lex_token token;





//-------------------------------------/
int main(){

  int error_flag = parser();

  if(error_flag==0){
    printf("File parsed sucessfully\n");
  }
  else{
    return(error_handler(error_flag));
  }



  token = get_token();
  printf("%d\n", token.value);


}
