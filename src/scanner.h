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

typedef enum{
  t_id,
  t_def,
  t_if,
  t_and,
  t_or,
  // atd...

}token_type;

// definice stavů lexikálního analyzátoru
typedef enum{
  start,
  key_word,
  integer,
  string,
  // TODO add more states
}lex_state;

// definice struktury tokenu posílaného z lexikálního analyzátoru
typedef struct{
    char value; // value of token
    int line;   // position of token
    int coll;
    token_type type;
}lex_token;
