/**
 * @file symtable.h
 *
 * Implemntace hash-table
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */
 #pragma once
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#define SYMTABLE_SIZE 27457

typedef enum{
  id,
  func,
  other,
}iType;

typedef struct Data_item{
  int data;
  iType type;
  char* params;
  char* retvals;
  bool defined;
  bool redef_flag;
  bool predefined;
}table_data;

typedef struct hash_table_item{ // structure of hash table
  char* identifier; // holds identifier
	table_data data;
  struct hash_table_item *next;
} Sym_table_item;


typedef Sym_table_item* Symtable[SYMTABLE_SIZE]; // array of items

// function prototypes

int                 table_error_handler           (int err_code, char* function);
unsigned long       Hash_function                 (const char *s);
void                table_init                    (Symtable *table);
bool                table_insert                  (Symtable *table, table_data data, char *identifier);
Sym_table_item      *search_in_table              (Symtable *table, char* identifier);
bool                table_remove                  (Symtable *table, char *identifier);
void                destroy_table                 (Symtable *table);
float               table_allocation_percentage   (Symtable *table);
bool                is_in_table                   (Symtable *table, char *identifier);
void                print_table                   (Symtable *table);
void                copy_table                    (Symtable *source, Symtable*dest);
void                set_redef_flag                (Symtable *table, bool flag);
void                set_redef_flag_by_id          (Symtable *table,char *id, bool flag);
