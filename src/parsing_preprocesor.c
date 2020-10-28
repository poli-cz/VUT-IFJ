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
#include "symtable.h"
#include "scanner.h"

int syntactic_prerun(Symtable *table){
  Tlist prerun;

  token_type test;




  while(prerun.next != NULL)

  prerun = *prerun.next; // Go to next token
}
