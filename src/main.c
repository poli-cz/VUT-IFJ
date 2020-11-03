#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Include user defined files //


#include "parser.h"



int main(){




return parser_debug();
}



int scanner_debug(){

  return 0;
}


int parser_debug(){


/*_____BEGIN SYMTABLE TESTS_____*/


  printf("---STACK TESTS---\n");

  /*_____________________________*/



  /*_____BEGIN STACK TESTS_____*/

  int pars_err = 0;
  int stack_err = 0;
  synt_stack stack;

  stack_init(&stack, stack_err);

  T_term term;
  term.type = t_lbra;
  tToken test;
  test.type = t_lbra;
  stack_push(stack, term, pars_err);
  if(stack_compare(stack, test)==1){
    printf("OK\n");
  }
  T_term term2;
  term2.type = t_id;
  stack_push(stack, term2, pars_err);
  if(stack_compare(stack, test)==0){
    printf("OK\n");
    stack_pop(stack, pars_err);
  }
  if(stack_compare(stack, test)==1){
    printf("OK\n");
  }


  // -----TESTS-----//
  stack_remove(&stack);
  printf("--STACK DONE---\n\n");

  /*_____________________________*/

  printf("---SYMTABLE TESTS---\n");
  Symtable test_tab;
  table_init(&test_tab);


  table_data tab_data;
  tab_data.data = 100;

  table_insert(&test_tab, tab_data, "data");

  if(is_in_table(&test_tab, "data")==1){
    printf("OK\n");
  }


  printf("---SYMTABLE DONE---\n");



  return parser();
}
