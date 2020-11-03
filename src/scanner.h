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
  t_id, //1
  t_error, //2
  t_def, //3
  t_if, //4
  t_and, //5
  t_or, //6
  t_eol, //7
  t_eof, //8
  t_mul, //9
  t_div, //10
  t_plus, //11
  t_minus, //12
  t_comma, //13
  t_semico, //14
  t_eq, //15
  t_float, //16
  t_assign, //17
  t_grt, //18
  t_lesst, //19
  t_lbra, //20
  t_rbra, //21
  t_colon, //22
  t_curll, //23
  t_curlr, //24
  t_exclam, //25
  t_neq, //26
  t_lst, //27
  t_grteq, //28
  t_lste, //29
  t_undefined, //30
  t_number, //31
  t_keyword, //32
  t_string, //33
  // NON TERMINALS
  n_prog,
  n_func,
  n_pkgmain,
  //atd..

}token_type;

// definice stavů lexikálního analyzátoru
typedef enum{
  s_error,
  s_start,
  s_id,
  s_key_word,
  s_number,
  s_floatpoint,
  s_float,
  s_exp,
  s_endcom,
  s_blockcom,
  s_meq,
  s_leq,
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
  s_exclam,
  s_fact,
  s_neq,
  s_key_word_id,
  s_linecom

  // TODO add more states
}lex_state;

// definice struktury tokenu posílaného z lexikálního analyzátoru
// definice struktury tokenu posílaného z lexikálního analyzátoru
typedef struct uh{
    dynamic_string* value; // value of token
    token_type type;
    struct uh *next;
    struct uh *prev;
}tToken;

// structure for holding list of tokens
typedef struct Token_list{
  tToken *first;
  tToken *last;
}tList;

tToken  get_token       ();
int  is_key_word     (dynamic_string* string);
int     parser          ();
void    print_token     (tToken token);
