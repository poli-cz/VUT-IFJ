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
  *stack = malloc(sizeof(struct SyntaxStack));

  if(!(*stack)){
    printf("malloc error\n");
    return;
  }
  (*stack)->top = 0;


  (*stack)->t = malloc(STACK_CHUNK_SIZE * sizeof(T_term));
  if(!(*stack)->t){
    printf("malloc error\n");
    return;
  }

  (*stack)->size = STACK_CHUNK_SIZE;
  //(*S)->a[0] = N_PROG; 				default non-terminal
}


bool stack_pop(synt_stack stack, int err_code){
  if((stack->top) == 0){
    printf("empty stack\n");
    return false;
  }
  stack->top--;
  return true;
}


bool stack_push(synt_stack stack, T_term term, int err_code){
  stack->size = stack->size + STACK_CHUNK_SIZE;
  stack->t = realloc(stack->t, stack->size * sizeof(T_term));
  stack->top++;
	stack->t[stack->top] = term;
  return true;
}

void stack_remove(synt_stack *stack){
  free((*stack)->t);
  free(*stack);
  *stack = NULL;
}


//  -------------------------------------------------------------- //
