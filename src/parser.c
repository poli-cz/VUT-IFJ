#include "scanner.c"
#include <stdbool.h>

// Main parsing function
int parser(){
  lex_token token;

  while(token.value!=EOF){
    token = get_token(token);
    printf("printing token values\n");
    printf("%s", token.value);


    if(token.value == 99){
      printf("\n\nwow, such an EOF..\n\n");
      return 0;
    }
    printf("%s", token.value);
  }





return 0;
}


// mock functions for now
int code_gen(){
  return 0;
}

int optimalization(){
  return 0;
}
