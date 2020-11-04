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

    printf("\n--------ENTERING PRERUN-------\n");
 // Loading tokens into linear list //
  tList tokens;
  tokens.last = NULL;
  tokens.first = NULL;
  while(1){
    tToken *token = (tToken*)(malloc(sizeof(tToken)));
    *token = get_token();
    // print_token(*token); // printing tokens for debug
    if(tokens.last == NULL){
      tokens.last = token;
      tokens.first = token;
    }
    else{
      tokens.last->next = token;
      tokens.last = tokens.last->next;
    }

  // check for lex-error aka. token_type == 1 //

    if(token->type == 1  ){  // CHECKING FOR RIGHT TOKENS
      printf("Token error\n");
      print_token(*token);
      error_handler(1);
    }
  //--------------------//

    if(token->type == 7){
      break;
    }
  }

// --------loading and listing tokens done--------------//




// Prohledávání kvůli klíčovým slovům a id a nahrávání do Sytable //


//----------FIRST PRERUN - loading functions----------//

  tToken test = (*tokens.first);
  bool pkg_main = 0;
  int func_count = 0;

  while(test.type != 7){

    // Check for package main //
    if((test.type == 31) && (strcmp(test.value->str, "package")==0)){
      tToken test2 = *test.next;
      if((test2.type == 0)&&(strcmp(test2.value->str, "main")==0)){
        pkg_main = 1;
        test = *test.next;
        continue;
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
//----------END FIRST PRERUN----------//

}
//----------SECOND PRERUN - loading variables----------//

  tToken run2 = (*tokens.first);
  while(run2.type != 7){
      if((run2.type == 0)&&(!is_in_table(g_table, run2.value->str))&&(strcmp(run2.value->str, "package")&&(strcmp(run2.value->str, "main")))){
        if(is_key_word(run2.value)==2){
          printf("Keyword as identifier\n"); // second check, I dont belive scanner..
          free(g_table);
          error_handler(3);
        }
        table_data iD;
        iD.type = id;
        iD.defined = false;
        table_insert(g_table, iD, run2.value->str);
      }

    run2 = *run2.next;
  }

//----------END SECOND PRERUN----------//

// --- LOAD INBUILT FCE IN SYMTABLE --- //
    table_data inbuilt_fce;
    inbuilt_fce.type = func;
    inbuilt_fce.defined = true;
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

// --- LOAD INBUILT FCE IN SYMTABLE --- //

    print_table(g_table);

    if(pkg_main == 0){
      printf("Missing prolog--ERROR--\n");
      destroy_table(g_table);
      error_handler(6);

    }
    if(is_in_table(g_table, "main")==0){
      printf("Missing main--ERROR--\n");
      destroy_table(g_table);
      error_handler(3);
    }

    printf("\n--------PRERUN Ok-------\n");
    return tokens;
}
