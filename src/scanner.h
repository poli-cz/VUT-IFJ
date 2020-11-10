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
#include <stdlib.h>
#include "dynamic_string.h"
#define KEYWORD_NUM 18



typedef enum{
  t_id,//0
  t_error,//1
  t_def,//2
  t_if,
  t_and,//4
  t_or,
  t_eol,//6
  t_eof,
  t_mul,//8
  t_div,
  t_plus,//10
  t_minus,
  t_comma,//12
  t_semico,
  t_eq,//14
  t_float,
  t_assign,//16
  t_grt,
  t_lesst,
  t_lbra,
  t_rbra,
  t_colon,
  t_curll,
  t_curlr,
  t_exclam,
  t_neq,
  t_lst,
  t_grteq,
  t_lste,
  t_undefined,
  t_number,
  t_keyword,
  t_string
  // atd...

}token_type;

// definice stavů lexikálního analyzátoru
typedef enum{
  s_error,
  s_start,
  s_id,
  s_number,
  s_floatpoint,
  s_float,
  s_exp,
  s_endcom,
  s_blockcom,
  s_string,
  s_eof,
  s_eol,
  s_mul,
  s_div,
  s_lslash,
  s_plus,
  s_minus,
  s_comma,
  s_semico,
  s_eq,
  s_assign,
  s_grt,
  s_lst,
  s_lbra,
  s_rbra,
  s_colon,
  s_curll,
  s_curlr,
  s_fact,
  s_neq,
  s_linecom

  // TODO add more states
}lex_state;

// definice struktury tokenu posílaného z lexikálního analyzátoru
typedef struct{
    dynamic_string* value; // value of token
    token_type type;
}tToken;

// structure for holding list of tokens
typedef struct Token_list{
  tToken t;
  struct Token_list *next;
  struct Token_list *first;
}Tlist;

// definition of used functions
tToken  get_token       ();
int  is_key_word     (dynamic_string* string);
int     parser          ();
void    print_token     (tToken token);
char    is_hexa         ();
