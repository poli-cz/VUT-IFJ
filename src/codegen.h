/**
 * @file codegen.h
 *
 * Hlavičkový soubor pro parser
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#include "parser.h"
#include <ctype.h>



void      main_code               ();
void      generate_params         (tToken token, Symtable *table, int rekurze_cnt);
void      expr_generator          (tToken token);
void      f_print                 (tToken token);
tToken    next_line               (tToken token);
void      call_params             (tToken token);
void      function_start          (Symtable *table, tToken token);
char      *stringToInterpret      (char *rawString);
void      id_solver               (tToken token, Symtable *table, int rekurze_cnt);
void      multi_solver            (tToken token, Symtable *table, int rekurze_cnt);
//char      *string_to_ifj      (char *string);
