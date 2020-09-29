#include<stdio.h>


// file for common functions and error handling

int error_handler(int code){
  switch (code) {
    case 1:
      fprintf(stderr, "chybná struktura aktuálního lexému\n");
      return(1);
    case 2:
      fprintf(stderr, "chybná syntaxe programu\n");
      return(2);
    case 3:
      fprintf(stderr, "chybná syntaxe programu\n");
      return(3);
    case 4:
      fprintf(stderr, "sémantická chyba\n");
      return(4);
    case 5:
      fprintf(stderr, "sémantická chyba typové kompatibility\n");
      return(5);
    case 6:
      fprintf(stderr, "špatný počet/typ parametrů či návratových hodnotu volání funkce či návratu z funkce.\n");
      return(6);
    case 7:
      fprintf(stderr, "ostatní sémantické chyby\n");
      return(7);
    case 9:
      fprintf(stderr, "sémantická chyba dělení nulovou konstantou.\n");
      return(9);
    default:
      fprintf(stderr, "interní chyba překladače\n");
      return(99);
    };
}
