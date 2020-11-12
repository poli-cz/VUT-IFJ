/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.h - hlavičkový soubor pro lexikální analyzátor
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    : Jan Polišenský (xpolis04)
 */
#pragma once
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
  t_string, //32
  t_ultime_skip, //33
  t_check_for_def_function, //34
  // sem si můžeš přidávat další typy
  // ale jenom opravdu na konec
  // NIC NEVKLADAT DOPROSTRED !!!



  // NON TERMINALS
  n_prog, //35
  n_func, //36
  n_param_n, //37
  n_retvals, //38
  n_body, //39
  n_fretvals, //40
  n_retval, // 41
  n_expr,   // 42
  n_body_id, // 43
  n_if,     //44
  n_for,    //45
  n_body_id_var, //46
  n_func_call, //47
  n_fretval, //48
  n_call_param, //49
  n_body_comma, //50
  n_def,        //51
  n_assign,     //52



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
  s_linecom,
  s_def

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
int     is_hexa         ();
