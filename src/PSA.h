/**
 * @file PSA.h
 *
 * Hlavičkový soubor pro PSA
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */
#pragma once
#include "parser.h"
#include <stdbool.h>
#define STACK_DEFAULT 1000


typedef enum{
  plus, //0
  minus, //1
  mul, //2
  ddiv, //3
  rela, //4
  l_bra, //5
  r_bra,// 6
  pid,   //7
  pint, //8
  pfloat, //9
  pstring, //10
  dolar, //11 like terminals

  shift,    // 12 <
  reduce,   // 13 >
  equal,    //14 =
  error,    //15

  final_E,   // 16 same behaviour like dolar

} Prec_table_sym;

//typedef struct token_val{
//
//
//}token_val;





typedef struct psateminal{
  Prec_table_sym sym;
  data_type data_type;

}PSA_term;

// structure of syntax_stact
typedef struct PSAStack{
    PSA_term *t;   // Pole neterminálů/terminálů
    int size;
    int top;    // Index prvního volného místa
	int last;   // Index naposledy vloženého prvku
}*psa_stack;

int       expr_parse          (Symtable *table, synt_stack stack, tToken token ,int err_code);
void      ps_stack_init       (psa_stack *stack);
bool      ps_stack_pop        (psa_stack stack);
bool      ps_stack_push       (psa_stack stack, PSA_term term);
void      ps_stack_remove     (psa_stack *stack);
void      ps_print_stack      (psa_stack stack);
void      reduce_rule         (psa_stack stack, int generate);
int       psa                 (tToken token, bool expr_print);
int       stack_shift_count   (psa_stack stack);
void      reduce_by_rule      (psa_stack stack, int count, int generate);
int       get_stack_top       (psa_stack);
