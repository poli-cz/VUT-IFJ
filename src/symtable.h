#define SYMTABLE_SIZE 27457

typedef struct Data_item{
  char* identifier;
  int test;
}table_data;

typedef struct hash_table_item{ // structure of hash table
  char* identifier;
	table_data data;
	struct hash_table_item *next;
} Sym_table_item;


typedef Sym_table_item* Symtable[SYMTABLE_SIZE]; // array of items
