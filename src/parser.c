/**
 * @file parser.c
 *
 * Hlavní tělo celého překladače
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */


#include <stdbool.h>
#include "parser.h"
#include "symtable.h"


// Main parsing function
int parser(){
  
  Symtable g_table;
  syntactic_prerun(&g_table);


return 0;
}




//  ------------------- Functions for work with synt_stack  ------------------- //



void stack_init(synt_stack *stack, int err_code){


}

// TODO //

// Stuctures for work with stack




bool stack_pop(synt_stack *stack, int err_code){


  // TODO //
  return true;
}


bool stack_push(synt_stack *stack, int err_code){

// TODO //

  return false;
}

void stack_remove(synt_stack *stack, int err_code){

// TODO //

}


//  -------------------------------------------------------------- //
