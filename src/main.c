#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Include user defined files //

#include "parser.c"
#include "basic.c"

int main(){
  int error_flag; // Main flag for catching errors

  error_flag = parser();

  if(error_flag != 0){
    printf("Error while parsing\n");
    return (error_handler(error_flag));
  }

  error_flag = code_gen();

  if(error_flag != 0){
    printf("Error while generating code\n");
    return (error_handler(error_flag));
  }

  error_flag = optimalization();

  if(error_flag == 0){
    printf("\n============================\n");
    printf("All compiled without error\n");
    return 0;
  }
  else{
    return (error_handler(error_flag));
  }
}
