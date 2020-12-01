/**
 * @file codegen.h
 *
 * Hlavičkový soubor pro parser
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#pragma once
#include <ctype.h>
#include "PSA.h"



void      main_code               ();
void      generate_params         (tToken token, Symtable *table, int rekurze_cnt);
void      expr_generator          (tToken token);
void      f_print                 (tToken token);
tToken    next_line               (tToken token);
void      call_params             (tToken token);
void      function_start          (Symtable *table, tToken token);
char      *stringToInterpret      (char *rawString);
char      *int_to_ifj             (char *rawInt);
char      *float_to_ifj           (char *rawFloat);
void      multi_solver            (tToken token, Symtable *table, int rekurze_cnt);
void      rela_parser             (tToken token);
bool      concat_check            (tToken token);
void      type_print              (tToken token);
char      *id_mannager            (tToken token);
void      for_id_definer          (tToken token, Symtable *get_table, Symtable *table);
int       get_id_top              (char *name);

//char      *string_to_ifj      (char *string);
