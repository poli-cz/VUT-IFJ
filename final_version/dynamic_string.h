/**
 * @file codegen.h
 *
 * Hlavičkový soubor pro dynamic_string
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xsveck00> Sabina Švecková
 */
#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H
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
int init_dynamc_string(dynamic_string **string);

/**
* Adds char at the end of array
*/
int add_char(char c,dynamic_string **string);

void free_string(dynamic_string **string);

#endif
