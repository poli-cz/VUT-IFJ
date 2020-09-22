/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.h - hlavičkový soubor pro lexikální analyzátor
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    : Jan Polišenský (xpolis04)
 */
#include <stdio.h>
#include <string.h>


// definice struktury tokenu posílaného z lexikálního analyzátoru
typedef struct{
    char* attribut;
    int value;
}lex_token;

// definice stavů lexikálního analyzátoru
typedef enum{
  error,
  EOL,
  integer,
  // there will be more states


}lex_state;
