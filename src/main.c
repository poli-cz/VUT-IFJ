#include <stdio.h>
#include <unistd.h>
#include "lex_token.c"


  lex_token token;

int main(){

    token = get_token();

    printf("%c\n", token.value);


    token = get_token();

    printf("%c\n", token.value);
}
