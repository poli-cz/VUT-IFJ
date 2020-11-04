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
  t_id, //0
  t_error, //1
  t_def, //2
  t_if, //3
  t_and, //4
  t_or, //5
  t_eol, //6
  t_eof, //7
  t_mul, //8
  t_div, //9
  t_plus, //10
  t_minus, //11
  t_comma, //12
  t_semico, //13
  t_eq, //14
  t_float, //15
  t_assign, //16
  t_grt, //17
  t_lesst, //18
  t_lbra, //19
  t_rbra, //20
  t_colon, //21
  t_curll, //22
  t_curlr, //23
  t_exclam, //24
  t_neq, //25
  t_lst, //26
  t_grteq, //27
  t_lste, //28
  t_undefined, //29
  t_number, //30
  t_keyword, //31
  t_pkgmain, //32
  t_string, //33
  // sem si můžeš přidávat další typy
  // ale jenom opravdu na konec
  // NIC NEVKLADAT DOPROSTRED !!!






  // NON TERMINALS
  n_prog, //34
  n_func, //35
  n_param_n, //36
  n_retvals, //37
  n_body, //38
  n_fretvals, //39
  n_retval, // 40

 // tady nic, dojebal by se mi parser, ale fakt ošklivým způsobem

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
int     is_key_word     (dynamic_string* string);
int     parser          ();
void    print_token     (tToken token);
