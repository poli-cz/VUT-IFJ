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
#include "basic.h"

/*
Implementation of PJW hash function
PJW hash algorithm involves shifting the previous
hash and adding the current byte followed by moving the high bits:
*/

int table_error_handler(int err_code, char* function){
  printf("Something in hash_table went teribly wrong\n");
  printf("%s exited with err_code %d\n", function, err_code);
  error_handler(99);
  return 0;
}


unsigned long Hash_function(const char *str){
  unsigned long hash = 0, x = 0;

for (char c = *str; c != '\0'; c = *(++str))
{
  hash = (hash << 4) + c;
  if ((x = hash & 0xF0000000L) != 0)
  {
    hash ^= (x >> 24);
  }
  hash &= ~x;
}
    return hash % SYMTABLE_SIZE;
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
bool table_insert(Symtable *table, table_data data, char *key){

  if((*table)==NULL){return 0;}
  else{
    Sym_table_item *temp = NULL;
    unsigned long hash = Hash_function(key);

    if((temp = search_in_table(table, key))==NULL){
      if((*table)[hash] == NULL){
        (*table)[hash] = malloc(sizeof(Sym_table_item));
        (*table)[hash]->identifier = key;
        (*table)[hash]->data = data;
        (*table)[hash]->next = NULL;
      }
      else{

        temp = malloc(sizeof(Sym_table_item));
        temp->identifier = key;
        temp->data = data;
        temp->next = (*table)[hash];
        (*table)[hash] = temp;
      }
    }
    else{

      if((temp = search_in_table(table, key))!=NULL){
        Sym_table_item *temp2;
        temp2 = (*table)[hash];
        while(!temp){
          if(temp2->identifier==key){
            temp2->data=data;
            return 1;
          }
          temp2=temp2->next;
        }
      }

    }
  }
  return true;
}
/*
Take structure  table_data as param, allocate memory for it,
calculate hash acording to key and insert to position in table

return position in table

*/
Sym_table_item *search_in_table(Symtable *table, char* identifier){

  unsigned long hash = Hash_function(identifier);

  if((*table)[hash] == NULL){
    return NULL;
  }
  else{
    Sym_table_item *temp = (*table)[hash];

    while(temp != NULL){
      if((strcmp(temp->identifier, identifier))==0){
        return (*table)[hash];
      }
      else{
        temp = temp->next;
      }
    }
  }
  return NULL;
}


bool is_in_table(Symtable *table, char* identifier){
  Sym_table_item *test;
  test = search_in_table(table, identifier);
  if(test == NULL ){
    return false;
  }
  else{
    return true;
  }

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
        //free((*table)[i]->data.params);
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

void print_table(Symtable *table){
  char *t;
  printf("------printing symtable-----\n\n");
  for(int i = 0; i<SYMTABLE_SIZE; i++){
    if((*table)[i] != NULL){
      if((*table)[i]->data.type == 0){
         t = "Variable";
         char* type;
         if((*table)[i]->data.d_type==0){
           type = "NDEF";
         }else if((*table)[i]->data.d_type==1){
           type = "INT";
         }else if((*table)[i]->data.d_type==2){
           type = "float64";
         }else if((*table)[i]->data.d_type==3){
           type = "string";
         }
         printf("%s with ID \"%s\" defined-> %d redef_flag-> %d value--> %s\n", t, (*table)[i]->identifier, (*table)[i]->data.defined, (*table)[i]->data.redef_flag, type);
      }

    }
  }
  printf("--------------------------------------------------------\n");
  for(int i = 0; i<SYMTABLE_SIZE; i++){
    if((*table)[i] != NULL){
      if((*table)[i]->data.type == 0){

      }
      else if((*table)[i]->data.type == 1){

        char *params = "";
        params = (*table)[i]->data.params;

         t = "Function";
         printf("%s with ID \"%s\" defined-> %d  with params--> \"%s\" retvals--> \"%s\"\n", t, (*table)[i]->identifier, (*table)[i]->data.defined, params, (*table)[i]->data.retvals);
      }
    //  else{
    //     t = "other";
    //     printf("%s with ID \"%s\" value-> %d \n", t, (*table)[i]->identifier, (*table)[i]->data.data);
    //}


    }
  }
  printf("\n--------end symtable-------\n");
}


void copy_table(Symtable *source, Symtable*dest){
  for(int i = 0; i<SYMTABLE_SIZE; i++){
    if((*source)[i] != NULL){
      table_insert(dest, (*source)[i]->data, (*source)[i]->identifier);
    }
  }
}




void set_redef_flag(Symtable *table, bool flag){
  for(int i = 0; i<SYMTABLE_SIZE; i++){
    if((*table)[i] != NULL){

          (*table)[i]->data.redef_flag = flag;
        }
    }

}

void set_redef_flag_by_id (Symtable *table,char *id, bool flag){
  for(int i = 0; i<SYMTABLE_SIZE; i++){
    if((*table)[i] != NULL){

        if(strcmp(id, (*table)[i]->identifier)==0){

          (*table)[i]->data.redef_flag = flag;
        }
    }
  }
}
