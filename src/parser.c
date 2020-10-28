/**
 * @file parser.c
 *
 * Hlavní tělo celého překladače
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */


#include "scanner.c"
#include <stdbool.h>
#include "symtable.c"
#include "parser.h"
#include "stdbool.h"

// Main parsing function
int parser(){
  int err_code;
  lex_token token;

  symtable global_table;  // initializing of symtables
  symtable local_table;
  symtable local_func_table;

  table_init(&global_table);
  table_init(&local_table);
  table_init(&local_func_table);

  synt_stack stack; // Stack pro rekurzivní sestup

  stack_init(&stack);

return 0;
}




//  ------------------- Functions for work with synt_stack  ------------------- //



void stack_init(synt_stack *stack, int err_code){
  *stack = malloc(sizeof(synt_stack));


  (*stack)->top = 1;
  (*stack)->last = 0

}

// TODO //

// Stuctures for work with stack




bool stack_pop(synt_stack *stack, int err_code){


  // TODO //
}


bool stack_push(synt_stack *stack, int err_code){

// TODO //

}

void stack_remove(synt_stack *stack, int err_code){

// TODO //

}


//  -------------------------------------------------------------- //
