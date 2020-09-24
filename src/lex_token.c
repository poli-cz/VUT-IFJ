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

lex_token get_token(){
  int c; // value from input
  FILE *fp; // open target file

  // we need to send state of lex and token //
  lex_token token;
  lex_state state;

   fp = fopen("test.go","r");
   if(fp==0){
     printf("error while readin file\n");
     return(token);
     // error while reading file
   }

   //-------------------------------------//

   // main reading loop

      c = getchar();

      if(feof(fp) == 1){
        printf("End of file\n");
        return(token);
      }

  // main reading switch //

        switch (c){
          case 13:
            token.value = 13;
            printf("ASCII token 13");
            break;
          case 12:
            token.value = 12;
            printf("ASCII token 12");
            break;
          case 11:
            token.value = 11;
            printf("ASCII token 11");
            break;
        }


      //printf("ASCII value of token %d\n",c);
      token.value = c;

      //printf("%c", c);


   fclose(fp);

   return(token);
}
