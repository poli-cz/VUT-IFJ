/**
 * @file parsing_preprocessor.cS
 *
 * Funkce pro syntaktický prerun
 * Vytváření zřetězeného seznamu tokenů pro analýzu
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#define _GNU_SOURCE
#include "parser.h"
#include <stdio.h>

tList syntactic_prerun(Symtable *g_table){

  //  printf("\n--------ENTERING PRERUN-------\n");
 // Loading tokens into linear list //
  tList tokens;
  tokens.last = NULL;
  tokens.first = NULL;
  while(1){
    tToken *token = (tToken*)(malloc(sizeof(tToken)));
    *token = get_token();

    if(DEBUG){print_token(*token);}

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
      fprintf(stderr, "Invalid token --> %s\n", (*token).value->str);
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
    if((test.type == t_keyword) && (strcmp(test.value->str, "package")==0)){
      tToken test2 = *test.next;

      if((test2.type == 0)&&(strcmp(test2.value->str, "main")==0)){
        pkg_main = 1;
        test = *test.next;
        continue;
      }
    }
    //--------------------//


    // Loading functions into Global symtable //
    if((test.type == t_keyword) && (strcmp(test.value->str, "func")==0)){
      test = *test.next;


      if(!is_in_table(g_table, test.value->str) && !is_key_word(test.value)){
        table_data id;

        id.params = get_params(test);
        id.retvals = get_retvals(test);
        id.type = func;
        id.defined = true;


        table_insert(g_table, id, test.value->str);

        func_count++;
      }
      else{
        fprintf(stderr, "PREFUN ERR, FUNCTION %s REDEFINED\n", test.value->str);
        destroy_table(g_table);
        error_handler(3);
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
          fprintf(stderr, "Keyword as identifier\n"); // second check, I dont belive scanner..
          destroy_table(g_table);
          error_handler(3);
        }
        tToken toktok;
        toktok = *run2.next;

        if(toktok.type == t_lbra){
          table_data iD;
          iD.type = func;
          iD.defined = false;
          table_insert(g_table, iD, run2.value->str);
        }

      }

    id_add(run2, g_table);
    run2 = *run2.next;
  }

//----------END SECOND PRERUN----------//


// --- LOAD INBUILT FCE IN SYMTABLE --- //


    table_data inbuilt_fce;
    inbuilt_fce.type = func;
    inbuilt_fce.defined = true;

    inbuilt_fce.params = "";
    inbuilt_fce.retvals = "string int";
    table_insert(g_table, inbuilt_fce, "inputs");
    inbuilt_fce.params = "";
    inbuilt_fce.retvals = "int int";
    table_insert(g_table, inbuilt_fce, "inputi");
    inbuilt_fce.params = "";
    inbuilt_fce.retvals = "float64 int";
    table_insert(g_table, inbuilt_fce, "inputf");
    inbuilt_fce.params = "term, term, term";
    inbuilt_fce.retvals = "";
    table_insert(g_table, inbuilt_fce, "print");
    inbuilt_fce.params = "int";
    inbuilt_fce.retvals = "float64";
    table_insert(g_table, inbuilt_fce, "int2float");
    inbuilt_fce.params = "float";
    inbuilt_fce.retvals = "int";
    table_insert(g_table, inbuilt_fce, "float2int");
    inbuilt_fce.params = "string";
    inbuilt_fce.retvals = "int";
    table_insert(g_table, inbuilt_fce, "len");
    inbuilt_fce.params = "string int int";
    inbuilt_fce.retvals = "string int";
    table_insert(g_table, inbuilt_fce, "substr");
    inbuilt_fce.params = "string int";
    inbuilt_fce.retvals = "int int";
    table_insert(g_table, inbuilt_fce, "ord");
    inbuilt_fce.params = "int";
    inbuilt_fce.retvals = "string int";
    table_insert(g_table, inbuilt_fce, "chr");


    table_data f_count;
    f_count.type = other;
    f_count.data = func_count;
    f_count.defined = true;

    table_insert(g_table, f_count, "function_count");


// --- LOAD INBUILT FCE IN SYMTABLE --- //




    if(pkg_main == 0){
      fprintf(stderr, "Missing prolog--ERROR--\n");
      destroy_table(g_table);
      error_handler(7);

    }
    if(is_in_table(g_table, "main")==0){
      fprintf(stderr, "Missing main--ERROR--\n");
      destroy_table(g_table);
      error_handler(3);
    }



    if(DEBUG){print_table(g_table);}
  //  print_table(g_table);
  //  print_table(g_table);
  //  exit(2);
    if(DEBUG){printf("\n--------PRERUN Ok-------\n");}


    return tokens;
}






char *get_retvals(tToken token){
  char *params= "";

  while(token.type != t_rbra){

    if(token.type == t_eof){
      return params;
    }
    token = *token.next;
  }
  token = *token.next;

  if(token.type == t_curll){
    return params;
  }
  else if(token.type == t_lbra){
    while(token.type != t_rbra){
      if(token.type == t_eof){
        return params;
      }

      if(token.type == t_keyword){
          if(-1 == asprintf(&params,"%s %s",token.value->str, params)){
            fprintf(stderr, "internal\n");
        }
      }
      token = *token.next;
    }
  }
  return params;
}



char *get_params(tToken token){
  token = *token.next; // skipp func name
  token = *token.next; // skipp l_brac
  char *params= "";

  while(token.type != t_rbra){
    if(token.type == t_eof){
      return params;
    }

    if(token.type == t_keyword){
        if(-1 == asprintf(&params,"%s %s",token.value->str, params)){
          fprintf(stderr, "internal\n");
      }
    }
    token = *token.next;
  }

  return params;
}

void  id_add(tToken token, Symtable *table){

    if(token.type == t_id){
      tToken next = *token.next;
      if(next.type == t_def){

        table_data iD;
        iD.type = id;
        iD.predefined = true;
        iD.redef_flag = 0;
        iD.defined = false;
        table_insert(table, iD, token.value->str);


      }
      else if(next.type == t_comma){
        table_data iD;
        iD.type = id;
        iD.predefined = true;
        iD.redef_flag = 0;
        iD.defined = false;
        table_insert(table, iD, token.value->str);
        next = *next.next;
        id_add(next, table);
      }
      else if(next.type == t_keyword){
        if((strcmp(next.value->str, "int")==0)||(strcmp(next.value->str, "float64")==0)||(strcmp(next.value->str, "string")==0)){
          table_data iD;
          iD.type = id;
          iD.predefined = true;
          iD.redef_flag = 0;
          iD.defined = false;
          table_insert(table, iD, token.value->str);
        }
      }
      else{
      }
    }













}
