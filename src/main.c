/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.c - lexikální analyzátor reprezentovaný konečným automatem
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    : Jan Polišenský (xpolis04)
 */



#include <stdio.h>
#include "scanner.h"




int main(){
  int c; // value from input
  FILE *fp; // open target file

  // we need to send state of lex and token //
  lex_token token;
  lex_state state;

   fp = fopen("test.go","r");
   if(fp==0){
     printf("error while readin file\n");
     return(0);
     // error while reading file
   }

   //-------------------------------------//

   // main reading loop
   while(1) {
      c = fgetc(fp);

      if(feof(fp) == 1){
        printf("End of file\n");
        return(0);
      }

  // main reading switch //
      switch (c){
        case 13:
          token.value = 13;
          printf("----End of line----");
          printf("%d", token.value);
          send_token();
          break;
      }


      printf("%c", c);
   }
   fclose(fp);

   return(0);
}
