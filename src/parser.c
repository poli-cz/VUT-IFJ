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



// Main parsing function
int parser(){
  int pars_err;
  Symtable g_table;
  synt_stack stack;

  table_init(&g_table);

  stack_init(&stack, pars_err);

  T_term term;
  term.type = t_lbra;

  tToken test;
  test.type = t_lbra;

  stack_push(stack, term, pars_err);

  printf("%d TRUE\n", stack_compare(stack, test));

  T_term term2;
  term2.type = t_id;

  stack_push(stack, term2, pars_err);

  printf("%d FALSE\n", stack_compare(stack, test));

  stack_pop(stack, pars_err);

  printf("%d TRUE \n", stack_compare(stack, test));

  printf("---SYMTABLE DONE---\n\n");
  tList pre = syntactic_prerun(&g_table);
  if((pre.last == NULL)&&(pre.first == NULL)){
    return 1;
  }


if(pars_err == 1){
  printf("there was error\n");
}
return 0;
}



//  ------------------- Functions for work with synt_stack  ------------------- //



bool stack_compare(synt_stack stack, tToken token){
//  printf("%d on  STACK\n", (stack->t[stack->top]).type);
//  printf("%d is TOKEN\n", (token.type));
  if((token.type)==(stack->t[stack->top]).type){
    return true;
  }
  else{
    return false;
  }


}

void stack_init(synt_stack *stack, int err_code){
  *stack = malloc(sizeof(struct SyntaxStack));

  if(!(*stack)){
    err_code = 1;
    return;
  }
  (*stack)->top = 1;
  (*stack)->last = 0;


  (*stack)->t = malloc(STACK_DEFAULT * sizeof(T_term));
  if(!(*stack)->t){
    err_code = 1;
    return;
  }

  (*stack)->size = STACK_DEFAULT;
}


bool stack_pop(synt_stack stack, int err_code){
  if((stack->top) == 0){
    printf("empty stack\n");
    err_code = 1;
    return false;
  }

  stack->top--;
  stack->last--;
  return true;
}

bool stack_push(synt_stack stack, T_term term, int err_code){
  if((stack->top)==(stack->size)){
    stack->size = stack->size + STACK_DEFAULT;
    stack->t = realloc(stack->t, stack->size * sizeof(T_term));
  }
  stack->top++;
	stack->t[stack->top] = term;
  stack->last++;
  return true;
}

void stack_remove(synt_stack *stack){
  free((*stack)->t);
  free(*stack);
  *stack = NULL;
}

//  -------------------------------------------------------------- //
