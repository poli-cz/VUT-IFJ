#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Include user defined files //


#include "parser.h"



int main(){


return parser_debug();

}



int scanner_debug(){
  // Dejte si sem funkce na debug scanneru

  return 0;
}


int parser_debug(){


/*_____BEGIN SYMTABLE TESTS_____*/

  Symtable table; //
  table_init(&table); // init symtable

  table_data test;
  test.data = 100;
  test.identifier = "int";
  table_insert(&table, test);

  table_data *data2 = search_in_table(&table, "int");

  float alloc = table_allocation_percentage(&table);

  if(data2->data == test.data){
    printf("Sucess\n");
  }

  table_remove(&table, "int");

  destroy_table(&table);
  printf("---SYMTABLE DONE---\n");

  /*_____________________________*/



  /*_____BEGIN STACK TESTS_____*/

  int stack_err;
  synt_stack stack;

  stack_init(&stack, stack_err);

  printf("%d\n", stack->top);
  printf("%d\n", stack->size);

  T_term terminal;
  terminal.test = 100;
  stack_push(stack, terminal, stack_err);
  printf("size of stack shoul differ\n");

  printf("%d\n", stack->top);
  printf("%d\n", stack->size);



  T_term term = stack->t[stack->top];
  if(term.test == terminal.test){
    printf("Ok\n");
  }

  stack_pop(stack, stack_err);

  term = stack->t[stack->top];
  if(term.test == 0){
    printf("Ok\n");
  }
  stack_remove(&stack);
  printf("--STACK DONE---\n");

  /*_____________________________*/

  printf("---TESTS DONE---\n");
  parser();






  return 0;
}
