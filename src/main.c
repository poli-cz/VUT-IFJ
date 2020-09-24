#include <stdio.h>
#include <unistd.h>
#include "scanner.c"

// Initializing of main variables //
  lex_state state;
  lex_token token;



//-------------------------------------/
int main(){

  for (int i = 0; i < 100; i++) {
    token = get_token();

    printf("%c", token.value);

  }


}
