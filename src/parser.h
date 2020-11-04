/**
 * @file symtable.c
 *
 * Hlavičkový soubor pro parser
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#include<stdbool.h>
#include "symtable.h"
#include "scanner.h"
#include "basic.h"
#define STACK_DEFAULT 1000
                    // Velikost alokační jednotky zásobníku

/**
 * Pomocný zásobník k rekurzivnímu sestupu, probíhá na něm rozklad neterminálů na terminály
 */




typedef struct teminal{
  int test;
  int k_w[20]; // keywords for check
  int used; // how many items are used
  bool k_check;
  token_type type;

}T_term;

// structure of syntax_stact
typedef struct SyntaxStack{
    T_term *t;   // Pole neterminálů/terminálů
    int size;
    int top;    // Index prvního volného místa
	int last;   // Index naposledy vloženého prvku
}*synt_stack;





// function prototypes

int       parser            ();
int       parser_debug      ();
int       scanner_debug     ();

void      stack_init        (synt_stack *stack, int err_code);
bool      stack_pop         (synt_stack stack, int err_code);
bool      stack_push        (synt_stack stack, T_term term, int err_code);
void      stack_remove      (synt_stack *stack);
bool      stack_compare     (synt_stack stack, tToken token);
tList     syntactic_prerun  (Symtable *table);

void      stack_expand      (Symtable *table, synt_stack stack, tToken token ,int err_code);
void      senor_clean_fist  (Symtable *table, synt_stack stack);
void      semantic_check    (Symtable *table, synt_stack stack, tToken token, int err_code);
void      print_stack       (synt_stack stack);
bool      is_correct_kword  (char* id, int which[20], int used);
