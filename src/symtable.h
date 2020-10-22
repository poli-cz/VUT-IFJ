/**
 * @file symtable.h
 *
 * Implemntace hash-table
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#define SYMTABLE_SIZE 27457

typedef struct Data_item{
  char* identifier;
  int data;
  // can be as much parameters as I want..
}table_data;

typedef struct hash_table_item{ // structure of hash table
  char* identifier; // holds identifier
	table_data data;
} Sym_table_item;


typedef Sym_table_item* Symtable[SYMTABLE_SIZE]; // array of items

// function prototypes
/*
unsigned long    Hash_function(const unsigned char *s);
void             table_init(Symtable *table);
bool             table_insert(Symtable *table, table_data data);
table_data*      search_in_table(Symtable *table, char* identifier);
bool             table_remove(Symtable *table, char *identifier);
void             destroy_table(Symtable *table);
*/
