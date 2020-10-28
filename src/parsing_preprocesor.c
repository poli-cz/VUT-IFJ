/**
 * @file parsing_preprocessor.c
 *
 * Funkce pro syntaktický prerun
 * Vytváření zřetězeného seznamu tokenů pro analýzu
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */



#include "parser.h"
#include "symtable.h"
// #include "scanner.c"




int syntactic_prerun(Symtable *table, Token_list Tlist){
  Tlist prerun = load_input();

  while(prerun.next != NULL)








  prerun = prerun.next; // Go to next token
}







Tlist load_input(){
// TODO load tokens and make from them linear list.
// Cause we need to store them...
}
