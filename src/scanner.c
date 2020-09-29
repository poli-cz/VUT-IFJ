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

  lex_token token; // structure of token in scanner.h
  char c; // curent char from stdin

  while(1){
    c = getchar();
    token.value = c;
    return(token);
  }


   return(token);
}
