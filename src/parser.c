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

  int pars_err = 0;
  Symtable g_table;
  synt_stack stack;

  table_init(&g_table);
  stack_init(&stack, pars_err);

  tList pre = syntactic_prerun(&g_table);

  if((pre.last == NULL) && (pre.first == NULL)){
    printf("PRERUN ERR\n");
    return 1;
  }
    printf("\n--------SYNTAX CHECK-------\n");

    tToken s_tok = (*pre.first); // Token for syntax check
    T_term p_term;
    p_term.type = n_prog;  // Default non terminal

    stack_push(stack, p_term, pars_err);

    while(s_tok.type != 7){ // until EOF

      if((stack->t[stack->top].type) > t_string){ // Non terminal on stack
      //  stack_expand(); TODO


      }
      else{
        //if(stack_compare() == true){
        //  stack_pop();
          // TODO semantic check //
      //  }
      //  else{
          // TODO place for raise syntax_err
      //  }

      }





      s_tok = *s_tok.next;
    }








return 0;
}



//  ------------------- Functions for work with synt_stack  ------------------- //



bool stack_compare(synt_stack stack, tToken token){
  printf("%d on  STACK\n", (stack->t[stack->top]).type);
  printf("%d is TOKEN\n", (token.type));
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

//  -----------------------SYNTAX STUFF--------------------------------------- //



void stack_expand(synt_stack stack, tToken token, int err_code ,Symtable *table){


// TODO























}

// Dealocation of everything //

void senor_clean_fist(Symtable *table, synt_stack stack){
  destroy_table(table);
  stack_remove(&stack);
}


//  -------------------------------------------------------------- //



//  -----------------------SEMANTIC STUFF-------------------------------------- //


// int parse_semantic(){





//}
