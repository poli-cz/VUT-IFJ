/**
 * @file PSA.h
 *
 * Hlavičkový soubor pro PSA
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */
#pragma once
#include "parser.h"
#include <stdbool.h>



int expr_parse(Symtable *table, synt_stack stack, tToken token ,int err_code);
