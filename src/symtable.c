/**
 * @file symtable.c
 *
 * Implemntace hash-table
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#include "symtable.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>


/*
Implementation of PJW hash function
PJW hash algorithm involves shifting the previous
hash and adding the current byte followed by moving the high bits:
*/

int table_error_handler(int err_code, char* function){
  printf("Something in hash_table went teribly wrong\n");
  printf("%s exited with err_code %d", function, err_code);
  exit(99);
  // 1 fatal errors like malloc error
  // 2 not so fatal error like search fault
  // 3 just warnings, like table is nearly allocated
}


unsigned long Hash_function(const char *s){
    unsigned long   h = 0, high;
    while (*s)
    {
        h = (h << 4) + *s++;
        if ((high = h) & 0xF0000000)
            h ^= high >> 24;
        h &= ~high;
    }
    return h % SYMTABLE_SIZE;
}

// Table init
// all items to NULL
void table_init(Symtable *table){
  for(int i = 0; i < SYMTABLE_SIZE; i++){
    (*table)[i] = NULL;
  }
}
/*
Take structure  table_data as param, allocate memory for it,
calculate hash acording to key and insert to position in table

return true or false

*/
bool table_insert(Symtable *table, table_data data){

  unsigned long hash = Hash_function(data.identifier); // calculate hash of item

  // if there is already some item than move to next and make same tes..
  while((*table)[hash] != NULL){
    //printf("shifting...\n");
    hash++;
  }

  // allocating memmory for inserted element
  Sym_table_item *t_data = (Sym_table_item*)malloc(sizeof(table_data));

  if(t_data == NULL) {
    table_error_handler(1, "table_insert");
    return false;
  }

  t_data->identifier = data.identifier;
  t_data->data = data;
  (*table)[hash] = t_data ;
  return true;
}
/*
Take structure  table_data as param, allocate memory for it,
calculate hash acording to key and insert to position in table

return position in table

*/
table_data *search_in_table(Symtable *table, char* identifier){

  unsigned long hash = Hash_function(identifier);

  if((*table)[hash] == NULL){
    table_error_handler(2, "search_in_table");
  }

  while((*table)[hash]->identifier != identifier){
    hash++;
  }
    return &(*table)[hash]->data;
  }

  /*
  Vyhledá v tabulce konkrétní prvek a vymaže ho..
  TODO: mazání zřetězených prvků je mega broken
  nebo spíš není

  */
bool table_remove(Symtable *table, char *identifier){

    unsigned long hash = Hash_function(identifier);

    if((*table)[hash] == NULL){
      table_error_handler(2, "search_in_table");
    }

    while((*table)[hash]->identifier != identifier){
      hash++;
    }
    free((*table)[hash]);
    (*table)[hash] = NULL;
    return true;
}


/*
Function to destroy all elements in table and free all memory

*/
void destroy_table(Symtable *table){
    for(int i = 0; i < SYMTABLE_SIZE; i++){
      if((*table)[i] != NULL ){
        free((*table)[i]);
        (*table)[i] = NULL;
      }
    }
}
/*
Function return symtable allocation percentage
try to keep it under 75%

*/

float table_allocation_percentage(Symtable *table){
  int free_position;
  for(int i = 0; i<SYMTABLE_SIZE; i++){
    if((*table)[i] == NULL){
      free_position++;
    }
  }
  float percentage = (free_position/SYMTABLE_SIZE)*100;

  if(percentage > 75.00){
    table_error_handler(3, "table_allocation_percentage");
  }
return percentage;
}

int main(){

Symtable table; //
table_init(&table); // init symtable


table_data test;
test.data = 100;
test.identifier = "int";
table_insert(&table, test);

table_data *data2 = search_in_table(&table, "int");

float alloc = table_allocation_percentage(&table);

printf("%f\n", alloc);

printf("%d\n", data2->data);
table_remove(&table, "int");

}
