/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.c - lexikální analyzátor reprezentovaný konečným automatem
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    : 
 */
<<<<<<< HEAD
#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H
=======

>>>>>>> 5073c44e4a2d66e2e6c0ff54dfe905a1978b8336
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
<<<<<<< HEAD
int init_dynamic_string(dynamic_string **string);
=======
int init_dynamic_string(dynamic_string** string);
>>>>>>> 5073c44e4a2d66e2e6c0ff54dfe905a1978b8336

/**
* Adds char at the end of array
*/
<<<<<<< HEAD
int add_char(char c,dynamic_string *string);

#endif
=======
int add_char(char c,dynamic_string* string);

>>>>>>> 5073c44e4a2d66e2e6c0ff54dfe905a1978b8336
