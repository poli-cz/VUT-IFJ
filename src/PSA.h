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
  plus_minus, //0
  mul, //1
  ddiv, //2
  rela, //3
  l_bra, //4
  r_bra,// 5
  iid, //6
  dolar, //7 like terminals

  shift,    // 8 <
  reduce,   // 9 >
  equal,    //10 =
  error,    //11

  final_E,   // 12 same behaviour like dolar

} Prec_table_sym;

typedef enum
{
	NT_EQ_NT,		/// E -> E = E
	NT_LEQ_NT,		/// E -> E <= E
	NT_LTN_NT,		/// E -> E < E
	NT_MEQ_NT,		/// E -> E => E
	NT_MTN_NT,		/// E -> E > E
	NT_PLUS_NT,		/// E -> E + E
	NT_MINUS_NT,	/// E -> E - E
	NT_IDIV_NT,		/// E -> E \ E
	NT_MUL_NT,		/// E -> E * E
	NT_DIV_NT,		/// E -> E / E
	LBR_NT_RBR,		/// E -> (E)
	OPERAND,		/// i -> E
	NOT_A_RULE		/// rule doesn't exist
} Prec_rules_enum;





typedef struct psateminal{
  Prec_table_sym sym;
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
void      reduce_rule         (psa_stack stack);
int       psa                 (tToken token);
int       stack_shift_count   (psa_stack stack);
void      reduce_by_rule      (psa_stack stack, int count);
int       get_stack_top       (psa_stack);
