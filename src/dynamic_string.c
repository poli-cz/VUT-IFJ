/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.c - lexikální analyzátor reprezentovaný konečným automatem
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    :
 * Inspired by functions in "jednoduchy_interpret"
 */
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_string.h"

/**
 * Initialise memory for array
 * If succesfull return 0, else return 1
*/

int init_dynamc_string(dynamic_string **string) {

    *string = (dynamic_string *)malloc(sizeof(dynamic_string));

    if (*string == NULL){
        fprintf(stderr, "Error allocating dynamic string\n");
        return 1;
    }

    (*string)->str = (char *)malloc(SIZE_ARR * sizeof(char));

    if ((*string)->str == NULL) {
        fprintf(stderr, "Error allocating dynamic string\n");
        free(*string);
        return 1;
    }

    (*string)->len = 0;
    (*string)->alloc = SIZE_ARR;
    (*string)->str[(*string)->len] = '\0';
    return 0;
}

/**
* Add char at the end of array. Realocate memory if necessary
* If successfull return 0, else return 1
*/

int add_char(char c, dynamic_string** string) {

    if ((*string)->len + 1 >= (*string)->alloc) {
        (*string)->str = (char*)realloc((*string)->str, (*string)->alloc + SIZE_ARR * (sizeof(char)));
        if ((*string)->str == NULL) {
            fprintf(stderr, "Error reallocating dynamic string\n");
            return 1;
        }
        (*string)->alloc += SIZE_ARR;
    }
    (*string)->str[(*string)->len] = c;
    (*string)->str[(*string)->len + 1] = '\0';
    (*string)->len++;

    return 0;
}
