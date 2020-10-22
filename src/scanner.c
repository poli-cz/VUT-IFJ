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
  lex_token token;


  // mock scanner just for testing //

  for(int i = 0; i < 10; i++){
    switch (i) {
      case 0:
        token.value = "package";
        token.line = 0;
        token.coll = 0;
        token.type = t_id;
      case 1:
        token.value = 99;
      }
    return token;
  }
/*
  package main

  func main(){
    print("Hello from IFJ@)", "\n")
  }
*/



   return(token);
}
