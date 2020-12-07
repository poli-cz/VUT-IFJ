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

// Definice typů položek v tabulce symbolů
typedef enum{
  id,
  func,
  other,
}iType;

// Definice datových typů přiřazovaných k id v symtable
typedef enum{
  type_NDEF,
  type_int,
  type_float64,
  type_string,
}data_type;


// Struktura jedné datové položky v tabulce symbolů
typedef struct Data_item{
  // Pro funkce //
  int data;
  iType type;
  char* params;
  char* retvals;
  bool defined;

  // pro Identifikátory //
  bool redef_flag;
  bool predefined;
  int level_flag;
  data_type d_type;

}table_data;


// Struktura samotné symtable
typedef struct hash_table_item{
  char* identifier;
	table_data data;
  struct hash_table_item *next;
} Sym_table_item;


typedef Sym_table_item* Symtable[SYMTABLE_SIZE];


// Prototypy funkcí pro práci s tabulkou symbolů

  // řeší chybové stavy v tabulce symbolů
int                 table_error_handler           (int err_code, char* function);
  // hašovací funkce popužita v ts
unsigned long       Hash_function                 (const char *s);
  // inicializace, vkládání, vyhledánáná a mazání položek v tabulce
void                table_init                    (Symtable *table);
bool                table_insert                  (Symtable *table, table_data data, char *identifier);
Sym_table_item      *search_in_table              (Symtable *table, char* identifier);
bool                table_remove                  (Symtable *table, char *identifier);

  // dealokace tabulky
void                destroy_table                 (Symtable *table);
float               table_allocation_percentage   (Symtable *table);

  // pomocné funkce pro změny určitých parametrů, nebo vypsání samotné tabulky
bool                is_in_table                   (Symtable *table, char *identifier);
void                print_table                   (Symtable *table);
void                copy_table                    (Symtable *source, Symtable*dest);

  // nastavování flagů použitých ke kontrole redefinic proměnných a funkcí
void                set_redef_flag                (Symtable *table, bool flag);
void                set_redef_flag_by_id          (Symtable *table,char *id, bool flag);
void                set_level_flag_by_id          (Symtable *table,char *id, int level);
void                set_level_flag                (Symtable *table, int level_flag);
