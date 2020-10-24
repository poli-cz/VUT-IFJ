/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.c - lexikální analyzátor reprezentovaný konečným automatem
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    : 
 */

#include <stdio.h>
#include <stdlib.h>
/**
* Initial size of array
*/
#define SIZE_ARR 8
/**
  * structure of dynamic array
  * *str - string,
  * length - length of string,
  * allocated - allocated memory for string
*/
typedef struct {
    char* str;
    unsigned int len;
    unsigned int alloc;
} dynamic_string;

/**
  *Initialise memory
*/
int init_dynamic_string(dynamic_string** string);

/**
* Adds char at the end of array
*/
int add_char(dynamic_string* string);