#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Include user defined files //

#include "scanner.h"
#include "parser.h"
#include "symtable.h"


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

  /*_____________________________*/

  //          TODO

  /*_____BEGIN STACK TESTS_____*/

  parser();












  return 0;
}
