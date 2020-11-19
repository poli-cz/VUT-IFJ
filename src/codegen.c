#include "codegen.h"


int generate_code(tList list, Symtable *table){
  if(DEBUG){printf("\n----GENERATING CODE----\n\n");}

  tToken token = (*list.first); // First token of program

  main_code(); // generate base code
  char* current_fce;

  while(token.type != 7){

// FUNCTION CALL

      if( is_fce(token.value->str, table) && strcmp("main", token.value->str) ){
        if(strcmp(token.value->str, "print")==0){
          f_print(token);
        }
        else{
          printf("CREATEFRAME\n");
          call_params(token);
          printf("CALL %s$\n", token.value->str);
        }

      }

// ASSIGN or DEF to id

      else if(token.type == t_id){

        if((*token.next).type == t_def){
          printf("DEFVAR LF@%s\n",token.value->str);
          generate_params(token, table); // solve expr or function call


        }else if((*token.next).type == t_assign){
          generate_params(token, table); // solve expr or function call


        }else if((*token.next).type == t_comma){
          // solve mutli a
// ----------------------------- //

}
    }
    else if(token.type == t_keyword){
      if(strcmp(token.value->str, "func")==0){
        printf("JUMP END%s$\n", (*token.next).value->str);
        printf("LABEL %s$\n", (*token.next).value->str);
        printf("CREATEFRAME\n");
        printf("PUSHFRAME\n");
        printf("DEFVAR LF@$return\n");
        function_start(table, token);
        current_fce = (*token.next).value->str;
      }

    // -------------CREATING FRAMES FOR SCOPES OR FUNCTIONS---------------- //
      else if(strcmp(token.value->str, "for")==0){
        //printf("CREATEFRAME\n");
        //expr_generator(token);

      }
      else if(strcmp(token.value->str, "else")==0){
        //printf("CREATEFRAME\n");

      }
      else if(strcmp(token.value->str, "if")==0){
        //printf("CREATEFRAME\n");
        //expr_generator(token);

      }
      else if(strcmp(token.value->str, "return")==0){
        // Udělat pomocí push and pop atd //


          expr_generator(*token.next);
          printf("MOVE LF@$return TF@$$retval\n");




      }

      // -------------FUNCTION CALL---------------- //

    }
    else if(token.type == t_curlr){
      if(strcmp(current_fce, "main")){
        printf("POPFRAME\n");
        printf("RETURN\n");
        printf("LABEL END%s$\n", current_fce);
      }
    }

  //  print_token(token);
    token = next_line(token);
  }



//printf("BREAK\n"); // JUST FOR DEBUG
return 0;
}



//------------------Parsing params of function call, quite dirty--------------------------//

void function_start(Symtable *table, tToken token){
  token = *token.next;
  token = *token.next;
  char *params[40][40];
  int p_counter = 0;


  while(token.type != t_rbra){
    if(token.type == t_id){
      params[p_counter][0] = token.value->str;
      p_counter++;
    }
    token = *token.next;
  }

  for (int i = 0; i < p_counter; i++) {
    printf("DEFVAR LF@%s\n",*params[p_counter-i-1]);
    printf("POPS LF@%s\n", *params[p_counter-i-1]);
  }
  printf("CLEARS\n");
}



// GENERATE VALUES FOR ASSIGN

void generate_params(tToken token, Symtable *table){
  char *name = token.value->str;

  token = *token.next; // Skip name
  token = *token.next; // skip assign or equal


  if(is_fce(token.value->str, table)){
    printf("CREATEFRAME\n");
    call_params(token);
    printf("CALL %s$\n", token.value->str);
    printf("MOVE LF@%s TF@$return\n", name);
    return;
  }else{

    expr_generator(token);
    printf("MOVE LF@%s TF@$$retval\n", name);
  }



}


//--------------------------------------------//

void expr_generator(tToken token){
  printf("CREATEFRAME\n");


  printf("DEFVAR TF@$$retval\n");
  printf("\n");
  psa(token, 1);
  printf("\n");
  printf("POPS TF@$$retval\n");


}


//--------------------------------------------//
void call_params(tToken token){

  token = *token.next; // skip func name
  while(token.type != t_eol){
    if(token.type== t_id){
      printf("PUSHS LF@%s\n",token.value->str);
    }else if(token.type == t_number){
      printf("PUSHS INT@%s\n",token.value->str);
    }else if(token.type == t_string){
      printf("PUSHS STRING@%s\n",token.value->str);
    } else if(token.type == t_float){
      printf("PUSHS FLOAT@%s\n",token.value->str);
    }
    token = *token.next;
  }
}

//--------------------------------------------//

tToken next_line(tToken token){
  if(token.type == t_eof){
    return token;
  }
  if(token.type == t_eol){
    return (*token.next);
  }
  else{
    while(token.type != t_eol){
      token = *token.next;
      if(token.type == t_eof){
        return token;
      }
    }
  }
  return (*token.next);
}
//--------------------------------------------//


//--------------------------------------------//
void f_print(tToken token){
  while(token.type!=t_eol){

    if(token.type == t_id){
      printf("WRITE LF@%s\n", token.value->str);
    }else if(token.type == t_string){
      printf("WRITE string@%s\n", stringToInterpret(token.value->str));
    }else if(token.type == t_float){

    }else if(token.type == t_number){
      printf("WRITE int@%s\n", token.value->str);
    }
    token = *token.next;
  }
}
//--------------------------------------------//
