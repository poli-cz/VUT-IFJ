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

tList syntactic_prerun(Symtable *g_table){

 // Loading tokens into linear list //
  tList tokens;
  tokens.last = NULL;
  tokens.first = NULL;
  while(1){
    tToken *token = (tToken*)(malloc(sizeof(tToken)));
    *token = get_token();
        print_token(*token);
    if(tokens.last == NULL){
      tokens.last = token;
      tokens.first = token;
    }
    else{
      tokens.last->next = token;
      tokens.last = tokens.last->next;
    }

  // check for lex-error aka. token_type == 1 //

    if(token->type == 99  ){  //1// // IGNORE FOR NOW // CHECKING FOR RIGHT TOKENS
      printf("Token error\n" );
      print_token(*token);
      tokens.last = NULL;
      tokens.first = NULL;
      return tokens;
    }
  //--------------------//

    if(token->type == 7){
      break;
    }
  }

// --------loading and listing tokens done--------------//




// Prohledávání kvůli klíčovým slovům a id a nahrávání do Sytable

  tToken test = (*tokens.first);
  bool func_flag;
  int f_count;
  bool pkg_main = 0;
  int func_count = 0;

  while(test.type != 7){



    // Check for package main //
    if((test.type == 0) && (strcmp(test.value->str, "package")==0)){
      tToken main = *test.next;
      if((main.type == 0)&&(strcmp(main.value->str, "main")==0)){
        pkg_main = 1;
      }
    }
    //--------------------//


    // Loading functions into Global symtable //
    if((test.type == 31) && (strcmp(test.value->str, "func")==0)){
      test = *test.next;

      if(!is_in_table(g_table, test.value->str) && !is_key_word(test.value)){
        table_data id;
        id.type = func;
        id.defined = true;
        table_insert(g_table, id, test.value->str);
        func_count++;
      }
    }
    else{
      test = *test.next;
    }
  //--------------------//

  }
  /*
  // --- LOAD INBUILT FCE IN SYMTABLE --- //
    table_data inbuilt_fce;
    table_insert(g_table, inbuilt_fce, "inputs");
    table_insert(g_table, inbuilt_fce, "inputi");
    table_insert(g_table, inbuilt_fce, "inputf");
    table_insert(g_table, inbuilt_fce, "print");
    table_insert(g_table, inbuilt_fce, "int2float");
    table_insert(g_table, inbuilt_fce, "float2int");
    table_insert(g_table, inbuilt_fce, "len");
    table_insert(g_table, inbuilt_fce, "substr");
    table_insert(g_table, inbuilt_fce, "ord");
    table_insert(g_table, inbuilt_fce, "chr");

  // --- JUST TESTS FOR PRESENCE IN TABLE --- //
    int is_there = 0;

    is_there += is_in_table(g_table, "inputs");
    is_there += is_in_table(g_table, "inputi");
    is_there += is_in_table(g_table, "inputf");
    is_there += is_in_table(g_table, "print");
    is_there += is_in_table(g_table, "int2float");
    is_there += is_in_table(g_table, "float2int");
    is_there += is_in_table(g_table, "len");
    is_there += is_in_table(g_table, "substr");
    is_there += is_in_table(g_table, "ord");
    is_there += is_in_table(g_table, "chr");

    if(is_there != 10){
      printf("some functions missing\n");
    }

*/


    print_table(g_table);

    if(pkg_main == 0){
      printf("Missing prolog--ERROR 6--\n");
    }
    if(is_in_table(g_table, "main")==0){
      printf("Missing main--ERROR 3--\n");
    }


    return tokens;
}
