/**
 * @file parsing_preprocessor.cS
 *
 * Funkce pro syntaktický prerun
 * Vytváření zřetězeného seznamu tokenů pro analýzu
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */


#include "parser.h"


int syntactic_prerun(Symtable *g_table){


  table_data id;
  id.identifier = "inputs";
  table_insert(g_table, id);

  table_data *data2 = search_in_table(g_table, "inputs");

  printf("%s\n", (*data2).identifier);
}
