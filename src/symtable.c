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
}


unsigned long Hash_function(const unsigned char *s){
    unsigned long   h = 0, high;
    while (*s)
    {
        h = (h << 4) + *s++;
        if (high = h & 0xF0000000)
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

return position in table



*/
bool table_insert(Symtable *table, table_data data){

  unsigned long hash = Hash_function(data.identifier); // calculate hash of item

  // if there is already some item than move to next and make same tes..
  while((*table)[hash] != NULL){
    printf("shifting...\n");
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
  printf("hash %d\n", hash);
  return true;
}

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


bool table_remove(Symtable *table, char *identifier){

    unsigned long hash = Hash_function(identifier);

    if((*table)[hash] == NULL){
      table_error_handler(2, "search_in_table");
    }

    while((*table)[hash]->identifier != identifier){
      hash++;
    }
    free((*table)[hash]);
}

void destroy_table(Symtable *table){
    for(int i = 0; i < SYMTABLE_SIZE; i++){
      if((*table)[i] != NULL ){
        free((*table)[i]);
        (*table)[i] = NULL;
      }
    }
}




// just function for testing table
int main(){


Symtable table; //
table_init(&table); // init symtable


table_data test;
test.test = 100;
test.identifier = "int";

bool position = table_insert(&table, test);

table_remove(&table, "int");







}
