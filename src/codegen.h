#include "parser.h"
#include <ctype.h>



void      main_code               ();
void      generate_params         (tToken token, Symtable *table);
void      expr_generator          (tToken token);
void      f_print                 (tToken token);
tToken    next_line               (tToken token);
void      call_params             (tToken token);
void      function_start          (Symtable *table, tToken token);
char      *stringToInterpret      (char *rawString);
//char      *string_to_ifj      (char *string);
