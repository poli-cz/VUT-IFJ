#include "codegen.h"


int generate_code(tList list, Symtable *table){
  if(DEBUG){printf("\n----GENERATING CODE----\n\n");}

  tToken token = (*list.first); // First token of program

  main_code(); // generate base code

  while(token.type != 7){
// CASES FOR GENERATING CODE...



// t_id
    if(token.type == t_id){
      if(0){

      }else if(0){

      }else if(0){

      }
// ----------------------------- //


    }
    else if(token.type == t_keyword){
      if(strcmp(token.value->str, "func")==0){
        // Definice funkce
        printf("LABEL %s$\n", (*token.next).value->str);
      }

      // --- here create frames --- //
      else if(strcmp(token.value->str, "for")==0){
        printf("CREATEFRAME\n");
      }
      else if(strcmp(token.value->str, "else")==0){

      }
      else if(strcmp(token.value->str, "if")==0){

      }
// ----------------------------- //
      else if((*token.next).type == t_lbra){
        // call of inbuilt function //

        printf("PUSHS string@%s\n", (*(*token.next).next).value->str);
        printf("CALL %s$\n", token.value->str);

      }
    }
    else if(token.type == t_eol){

// ----------------------------- //
//----TODO ----//
    }
    else if(0){

// ----------------------------- //
//----TODO ----//
    }
    else if(0){

// ----------------------------- //
//----TODO ----//
    }
    else if(0){

// ----------------------------- //
//----TODO ----//
    }
    else if(0){

    }
// ----------------------------- //
//----TODO ----//


    token=*token.next;
  }

return 0;
}
