/**
 * @file parser.c
 *
 * Hlavní tělo celého překladače
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */


#include <stdbool.h>
#include "parser.h"
#include "PSA.h"


// Main parsing function
int parser(){

  int pars_err = 0;
  Symtable g_table;
  synt_stack stack;

  table_init(&g_table);
  stack_init(&stack, pars_err);

// semantic prerun, only check for some basic semantic actions
  tList pre = syntactic_prerun(&g_table);

    if(DEBUG){printf("\n--------SYNTAX CHECK-------\n");}

    tToken s_tok = (*pre.first); // Token for syntax check
    T_term p_term;
    p_term.type = n_prog;  // Default non terminal

    stack_push(stack, p_term, pars_err);


    while(1){ // until EOF

      if(DEBUG){printf("-----------------\n");}
      if(DEBUG){print_token(s_tok);}
      if(DEBUG){printf("-----------------\n");}
      if(DEBUG){print_stack(stack);}

      if((stack->t[stack->top].type) > t_check_for_def_function){ // Non terminal on stack

        if(DEBUG){printf("EXPAND\n");}

        stack_expand(&g_table, stack, s_tok, pars_err);
      }
      else{
        if(stack_compare(stack, s_tok, &g_table) == true){
          stack_pop(stack, pars_err);



// --------EMPTY STACK--- ANALYSIS--DONE--------------------//
          if((stack->top==1)&&(s_tok.type == 7)){
            if(DEBUG){printf("\n-------------SYNTAX OK-------------\n");}
            break;
          }
          else if((stack->top!=1)&&(s_tok.type == 7)){
            fprintf(stderr, "unexpected EOF\n Returning error 2\n");
            senor_clean_fist(&g_table, stack, pre);
            error_handler(2);
          }
        }

//----------------------------------------------------------//

        else{
          fprintf(stderr, "Syntax check failed\n");
          senor_clean_fist(&g_table, stack, pre);
          error_handler(2);
        }
        s_tok = *s_tok.next;
      }
    }

//----------------------------------------------------------------------//



//----------------------------------------------------------------------//
//---------------------------SEMANTIC-CHECK-----------------------------//
//----------------------------------------------------------------------//

/*  Some semantic checks are done in preprocesor and also in syntax
    Mainly checking for undefined functions and that kind of stuff

*/

 int err = semantic_check(&g_table, stack, pre, pars_err);


 if(err != 0){
   senor_clean_fist(&g_table, stack, pre);
   error_handler(err);
 }else{
   senor_clean_fist(&g_table, stack, pre);
 }




if(DEBUG){printf("\n----ALL GOOD----\n\n");}

return 0;
}








//------------------------------------------------------------------------------//
//  ------------------- Functions for work with synt_stack  ------------------- //



bool stack_compare(synt_stack stack, tToken token, Symtable *table){
  if(DEBUG){printf("%d on  STACK\n", (stack->t[stack->top]).type);}
  if(DEBUG){printf("%d is TOKEN\n", (token.type));}


// ----- aditional check for Kword name -------//
  if((stack->t[stack->top]).k_check == true){
    if(token.type != t_keyword){
      if(DEBUG){printf("Bad Keyword\n");}
      return false;
    }
    bool ok = is_correct_kword(token.value->str, (stack->t[stack->top]).k_w, (stack->t[stack->top]).used);
    if(!ok){
  //    printf("Bad Keyword\n");
      return false;
    }
  }

// ---------------------------------------------//

//-------check for defined function -------------//
  if((stack->t[stack->top]).type == t_check_for_def_function){ // semantic check for defined function
    if(is_fce(token.value->str, table)==1){

      return true;            // we dont need to do pop, only check is there is defined function in token
    }
    else{
      fprintf(stderr, "Function used before definition\n");
      error_handler(3);
      return false;
    }
  }
// ---------------------------------------------//

if((stack->t[stack->top]).type == t_ultime_skip){
  return true;
}


  if((token.type)==(stack->t[stack->top]).type){
    return true;
  }
  else{
    return false;
  }
}



void stack_init(synt_stack *stack, int err_code){
  *stack = malloc(sizeof(struct SyntaxStack));

  if(!(*stack)){
    err_code = 1;
    return;
  }
  (*stack)->top = 1;
  (*stack)->last = 0;


  (*stack)->t = malloc(STACK_DEFAULT * sizeof(T_term));
  if(!(*stack)->t){
    err_code = 1;
    return;
  }

  (*stack)->size = STACK_DEFAULT;
}


bool stack_pop(synt_stack stack, int err_code){
  if((stack->top) == 0){
  //  printf("empty stack\n");
    err_code = 1;
    return false;
  }

  stack->top--;
  stack->last--;
  return true;
}

bool stack_push(synt_stack stack, T_term term, int err_code){
  if((stack->top)==(stack->size)){
    stack->size = stack->size + STACK_DEFAULT;
    stack->t = realloc(stack->t, stack->size * sizeof(T_term));
  }
  stack->top++;
	stack->t[stack->top] = term;
  stack->last++;
  return true;
}

void stack_remove(synt_stack *stack){
  free((*stack)->t);
  free(*stack);
  *stack = NULL;
}



bool is_in_stack(synt_stack stack, token_type type){

  for(int i = 0; i < stack->top; i++){
    if((stack->t[(stack->top)-i].type)==type){
      return true;
    }
  }
return false;
}

//  -----------------------SYNTAX STUFF--------------------------------------- //



void stack_expand(Symtable *table, synt_stack stack, tToken token ,int err_code){
  T_term ex_term;
  ex_term.k_check = false;

  if((stack->t[stack->top].type) == n_prog){ // non terminal N_PROG
    if(token.type == t_eol){

    stack_pop(stack, err_code); // Destroy current non terminal
    ex_term.type = n_prog;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_eol;
    stack_push(stack, ex_term, err_code);

    }
    else{
    stack_pop(stack, err_code); // Destroy current non terminal

    ex_term.type = n_func;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_id;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_keyword;
    stack_push(stack, ex_term, err_code);
    }
  }

  //---------------------FUNC----------------------------------//
  else if((stack->t[stack->top].type) == n_func){ // non terminal N_FUNC
    if(token.type == t_eol){

    stack_pop(stack, err_code); // Destroy current non terminal
    ex_term.type = n_func;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_eol;
    stack_push(stack, ex_term, err_code);

    }
    else if(token.type == t_eof){
    stack_pop(stack, err_code); // Destroy current non terminal
    ex_term.type = t_eof;
    stack_push(stack, ex_term, err_code);
    }
    else{
    stack_pop(stack, err_code); // Destroy current non terminal

    ex_term.type = n_func;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_curlr;
    stack_push(stack, ex_term, err_code);
    ex_term.type = n_fretvals;
    stack_push(stack, ex_term, err_code);
    ex_term.type = n_body;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_curll;
    stack_push(stack, ex_term, err_code);
    ex_term.type = n_retvals;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_rbra;
    stack_push(stack, ex_term, err_code);
    ex_term.type = n_param_n;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_lbra;
    stack_push(stack, ex_term, err_code);
    ex_term.type = t_id;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_keyword;
    ex_term.k_w[0] = 6; // check for FUNC key word
    ex_term.k_check = true;
    ex_term.used = 1;
    stack_push(stack, ex_term, err_code);
    ex_term.k_check = false;
      }
  }
  // ---------------------------PARSING FUNCTION PARAMETERS------------------//
  else if((stack->t[stack->top].type) == n_param_n){
    if(token.type == t_rbra){ // there are no other parameters
      stack_pop(stack, err_code); // Destroy n_params_n
    }

    else if(token.type == t_comma){
      stack_pop(stack, err_code);// Destroy n_params_n

      ex_term.type = n_param_n;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_keyword;
      ex_term.k_w[0] = 5; // check for double
      ex_term.k_w[1] = 7; // check for int
      ex_term.k_w[2] = 9; // check for string
      ex_term.k_check = true;
      ex_term.used = 3;
      stack_push(stack, ex_term, err_code);
      ex_term.k_check = false;

      ex_term.type = t_id;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_comma;
      stack_push(stack, ex_term, err_code);

    }
    else{
      stack_pop(stack, err_code);// Destroy n_params_n

      ex_term.type = n_param_n;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_keyword;
      ex_term.k_w[0] = 5; // check for double
      ex_term.k_w[1] = 7; // check for int
      ex_term.k_w[2] = 9; // check for string
      ex_term.k_check = true;
      ex_term.used = 3;
      stack_push(stack, ex_term, err_code);
      ex_term.k_check = false;

      ex_term.type = t_id;
      stack_push(stack, ex_term, err_code);

  // --------------------------------------------------------------------//

    }
  }
    //---------------------RETURN VALUES FROM FUNCTION----------------------------------//
  else if((stack->t[stack->top].type) == n_retvals){
    if(token.type == t_curll){ // there are no other parameters
      stack_pop(stack, err_code); // Destroy n_retvals
    }
    else{
      stack_pop(stack, err_code); // Destroy n_retvals

      ex_term.type = t_rbra;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_retval;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_keyword;
      ex_term.k_w[0] = 5; // check for double
      ex_term.k_w[1] = 7; // check for int
      ex_term.k_w[2] = 9; // check for string
      ex_term.k_check = true;
      ex_term.used = 3;
      stack_push(stack, ex_term, err_code);
      ex_term.k_check = false;

      ex_term.type = t_lbra;
      stack_push(stack, ex_term, err_code);
    }
  }
  else if((stack->t[stack->top].type) == n_retval){

    if(token.type == t_rbra){ // there are no other parameters
      stack_pop(stack, err_code); // Destroy
    }
    else{
      stack_pop(stack, err_code);// Destroy

      ex_term.type = n_retval;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_keyword;
      ex_term.k_w[0] = 5; // check for double
      ex_term.k_w[1] = 7; // check for int
      ex_term.k_w[2] = 9; // check for string
      ex_term.k_check = true;
      ex_term.used = 3;
      stack_push(stack, ex_term, err_code);
      ex_term.k_check = false;

      ex_term.type = t_comma;
      stack_push(stack, ex_term, err_code);
    }
  }
    //---------------------RETURN VALUES INSIDE FUNCTION----------------------------------//
  else if((stack->t[stack->top].type) == n_fretval){
    if(token.type == t_comma){
      ex_term.type = n_fretval;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_comma;
      stack_push(stack, ex_term, err_code);
    }
    else if(token.type == t_eol){
      stack_pop(stack, err_code);// Destroy

      ex_term.type = n_fretval;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);
    }
    else if(token.type = t_curlr){
      stack_pop(stack, err_code);// Destroy

    //  ex_term.type = t_curlr;
    //  stack_push(stack, ex_term, err_code);
    }
    else{
      fprintf(stderr, "UNEXPECTED IN function retvals\n");
      exit(2);
    }
  }

  //---------------------MAIN FUNCTION BODY----------------------------------//
  else if((stack->t[stack->top].type) == n_body){
    if(token.type == t_eol){
      stack_pop(stack, err_code); // Destroy

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);
      }
    else if(is_fce(token.value->str, table)==1){
      stack_pop(stack, err_code);

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_func_call;
      stack_push(stack, ex_term, err_code);

      }
    else if(token.type == t_curlr){
      stack_pop(stack, err_code); // Destroy

    //  ex_term.type = n_func_call;
    //  stack_push(stack, ex_term, err_code);
      }
    else if(token.type == t_number){
      stack_pop(stack, err_code); // Destroy


      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_expr; // cal precedent analysis
      stack_push(stack, ex_term, err_code);


    }
    else if(token.type == t_id){
      stack_pop(stack, err_code); // Destroy

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_body_id;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_id;
      stack_push(stack, ex_term, err_code);
    }
    else if(strcmp("if", token.value->str)==0){
      stack_pop(stack, err_code); // Destroy

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_if;
      stack_push(stack, ex_term, err_code);
    }
    else if(strcmp("for", token.value->str)==0){
      stack_pop(stack, err_code);

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);

      ex_term.type =n_for;
      stack_push(stack, ex_term, err_code);
    }
    else if(strcmp("return", token.value->str)==0){
      stack_pop(stack, err_code);
    }
    else{
      fprintf(stderr, "UNEXPECTED token in BODY\n");
      exit(2);
    }

  }
    //---------------------IF THERE IS ID----------------------------------//
  else if((stack->t[stack->top].type) == n_body_id){
      if(token.type == t_assign){
        stack_pop(stack, err_code);

        ex_term.type = n_body_id_var;
        stack_push(stack, ex_term, err_code);

        ex_term.type = t_assign;
        stack_push(stack, ex_term, err_code);
      }
      else if(token.type == t_def){
        stack_pop(stack, err_code);

        ex_term.type = n_body_id_var;
        stack_push(stack, ex_term, err_code);

        ex_term.type = t_def;
        stack_push(stack, ex_term, err_code);
      }
      else if(token.type == t_comma){ // assigning multiple variables
        stack_pop(stack, err_code);

        ex_term.type = n_body_id;
        stack_push(stack, ex_term, err_code);

        ex_term.type = t_id;
        stack_push(stack, ex_term, err_code);

        ex_term.type = t_comma;
        stack_push(stack, ex_term, err_code);
      }

      else{   // AM I supposed to give error?
        fprintf(stderr, "Unexpected token after ID \n");
        //print_token(token);
        //senor_clean_fist(table, stack, err_code);
        error_handler(2);
      }
  }
    //---------------------ASSIGNING MORE THAN ONE VARIABLE----------------------------------//
  else if((stack->t[stack->top].type) == n_body_comma){

    ex_term.type = n_body_id_var;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_def;
    stack_push(stack, ex_term, err_code);


  }
  else if((stack->t[stack->top].type) == n_body_id_var){

      if(token.type == t_eol){
        fprintf(stderr, "Expected ASSIGN\n"); // EOL here somehow causing SIGSEGV
        error_handler(2);
      }

      else if(is_fce(token.value->str, table)==1){
        stack_pop(stack, err_code);

        ex_term.type = n_func_call;
        stack_push(stack, ex_term, err_code);
      }
      else if(token.type == t_comma){
        stack_pop(stack, err_code);

        ex_term.type = t_comma; // cal precedent analysis
        stack_push(stack, ex_term, err_code);

        ex_term.type = n_expr; // cal precedent analysis
        stack_push(stack, ex_term, err_code);

      }
      else if(token.type == t_eol){
        stack_pop(stack, err_code);

        ex_term.type = t_eol; // cal precedent analysis
        stack_push(stack, ex_term, err_code);
      }

      else{
        stack_pop(stack, err_code); // Destroy

        //ex_term.type = n_body_id_var;
        //stack_push(stack, ex_term, err_code);

        ex_term.type = n_expr; // cal precedent analysis
        stack_push(stack, ex_term, err_code);
      }
  }
  else if((stack->t[stack->top].type) == n_fretvals){
    if(token.type == t_eol){
      stack_pop(stack, err_code);// Destroy

      ex_term.type = t_eol; // no nevim
      stack_push(stack, ex_term, err_code);

    }
    else if(token.type == t_keyword){
      stack_pop(stack, err_code);// Destroy

      ex_term.type = n_fretval;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_keyword;
      ex_term.k_w[0] = 8;
      ex_term.k_check = true;
      ex_term.used = 1;
      stack_push(stack, ex_term, err_code);
      ex_term.k_check = false;
    }
    else if(token.type == t_curlr){
      stack_pop(stack, err_code);// Destroy
    }
    else{
      fprintf(stderr, "UNEXPECTED token in return values of function\n");
      exit(2);
    }
  }
  // -------------------------------WRITE EXTERN FUNCTION-------------------//

/*
* Calling extern function to parse expresions
* this piece of code will generate n-universal tokens for stack pop
* this depence on <expr> lenght
* This is kind tricky, so be aware to touch this
*/
  else if((stack->t[stack->top].type) == n_expr){

  // from PSA we know how many token we should skip or pop

      int skip = expr_parse(table, stack, token, err_code);

      stack_pop(stack, err_code); // Destroy <n_expr>


      for(int i = 0; i < skip; i++){ // push universal tokens

        ex_term.type = t_ultime_skip;
        stack_push(stack, ex_term, err_code);
      }


  }

// -----------------------------------------------------------------------//
// -----------------------------------------------------------------------//



    //---------------------CALLING FUNCTION IN BODY----------------------------------//
  else if((stack->t[stack->top].type) == n_func_call){
      stack_pop(stack, err_code);

      //ex_term.type = n_body; body already generated
      //stack_push(stack, ex_term, err_code);

      ex_term.type = t_rbra;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_call_param;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_lbra;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_check_for_def_function;
      stack_push(stack, ex_term, err_code);
  }

    //---------------------PARSING PARAMETERS OF FUNCTION CALL ----------------------------------//
  else if((stack->t[stack->top].type) == n_call_param){
    if(token.type == t_rbra){
      stack_pop(stack, err_code);
    }
    else if(token.type == t_comma){
      stack_pop(stack, err_code);

      ex_term.type = n_call_param;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_comma;
      stack_push(stack, ex_term, err_code);
    }
    else{
      stack_pop(stack, err_code);

      ex_term.type = n_call_param;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);
    }
  }
      //---------------------PARSING IF----------------------------------//
  else if((stack->t[stack->top].type) == n_if){
    stack_pop(stack, err_code);

    ex_term.type = t_curlr;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_fretvals;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_body;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_curll;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_keyword;
    ex_term.k_w[0] = 3;
    ex_term.k_check = true;
    ex_term.used = 1;
    stack_push(stack, ex_term, err_code);
    ex_term.k_check = false;

    ex_term.type = t_curlr;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_fretvals;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_body;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_curll;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_expr;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_keyword;
    ex_term.k_w[0] = 2;
    ex_term.k_check = true;
    ex_term.used = 1;
    stack_push(stack, ex_term, err_code);
    ex_term.k_check = false;
  }
        //---------------------PARSING FOR----------------------------------//
  else if((stack->t[stack->top].type) == n_for){
    stack_pop(stack, err_code);

    ex_term.type = t_curlr;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_fretvals;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_body;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_curll;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_assign;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_semico;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_expr;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_semico;
    stack_push(stack, ex_term, err_code);

    ex_term.type = n_def;
    stack_push(stack, ex_term, err_code);

    ex_term.type = t_keyword;
    ex_term.k_w[0] = 4;
    ex_term.k_check = true;
    ex_term.used = 1;
    stack_push(stack, ex_term, err_code);
    ex_term.k_check = false;
  }
        //---------------------DEFINITION INSIDE FOR----------------------------------//
  else if((stack->t[stack->top].type) == n_def){
    if(token.type == t_semico){
      stack_pop(stack, err_code);
    }
    else{
      stack_pop(stack, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_def;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_id;
      stack_push(stack, ex_term, err_code);
    }
  }
        //---------------------ASSIGN INSIDE FOR----------------------------------//
  else if((stack->t[stack->top].type) == n_assign){
    if(token.type == t_curll){
      stack_pop(stack, err_code);
    }
    else{
      stack_pop(stack, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_assign;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_id;
      stack_push(stack, ex_term, err_code);
    }
  }

// This should NEVER happen, if so... we are all DOOMED :)
  else{
    fprintf(stderr, "UNEXPECTED NON_TERMINAL ON STACK \n");
    exit(99);
  }
}

//  -------------------------------------------------------------- //



//  -----------------------SEMANTIC STUFF-------------------------------------- //

int semantic_check(Symtable *table, synt_stack stack, tList list, int err_code){
  if(DEBUG){printf("\n-----------SEMANTIC CHECK----------\n" );}

  Symtable *local_table;
  tToken token = (*list.first);




  while(token.type != 7){

    // 1) Call without definition
    if((token.type == t_id)&&((*token.next).type == t_lbra)){
      if(is_fce(token.value->str ,table)){
        if(is_defined(token.value->str ,table)==0){
          fprintf(stderr, "FUNCTION %s NOT DEFINED\n", token.value->str);
          return 3;
        }
      }
    }
    // 2) Creating local frame for each function
    // Check definition stuff with localframe

    if((token.type == t_keyword) && (strcmp(token.value->str, "func") == 0)){
      tToken func = *token.next;
      Symtable local_table;
      bool fce_end = 1;
      table_init(&local_table);


      char *func_name = func.value->str;
      func = *func.next;

      table_data def;
      def.type = id;
      def.defined = true;
      table_insert(&local_table, def, "_");

      if(DEBUG){printf("BUILDED LOCAL FRAME for %s\n", func_name);}
      if(DEBUG){printf("------------------------------\n");}


// TODO -- load parameters of function and correct return //

// --------------------------------------------------------//

      while(fce_end){
      //  print_table(&local_table);
        id_check(func, &local_table, table);
        func = scope_check(func, table, &local_table);

        if(func.type == t_keyword){
          if(strcmp(func.value->str, "func") == 0){
            fce_end = 0;
          }
        }
        else if(func.type == t_eof){
          fce_end = 0;
        }
        func = *func.next;
      }
      destroy_table(&local_table);
    }
//-----------------------END LOCAL FRAME----------------------//



  token = *token.next;
}




return 0;
}






// Function to check for right id definition or redefinition
// TOTAL MESS, dont touch it until it works
void id_check(tToken func, Symtable *local_table, Symtable *table){

  if((func.type == t_id)&&(!is_fce(func.value->str ,table))){
    if((*func.next).type == t_def){

      if(is_in_table(local_table, func.value->str)){
        Sym_table_item *temp;
        temp = search_in_table(local_table, func.value->str);

      if(temp->data.redef_flag == 0){
        set_redef_flag_by_id(local_table, func.value->str, 1);
      }
      else{
        if(is_defined(func.value->str, local_table)){
          fprintf(stderr, "Variable %s redefined\n", func.value->str);
          error_handler(3);
        }
        else{
          table_data iD;
          iD.type = id;
          iD.defined = true;
          iD.redef_flag = 1;
          table_insert(local_table, iD, func.value->str);

        }
      }
    }
    else{
      table_data iD;
      iD.type = id;
      iD.defined = true;
      iD.redef_flag = 1;
      table_insert(local_table, iD, func.value->str);

    }

      tToken call = *func.next;
      call = *call.next;

      if(is_fce(call.value->str, table)){
        //fprintf(stderr, "Cant initialize variable with function ASSIGN\n" );
        //error_handler(3);
      }
    }
    else if((*func.next).type == t_assign){
      if(is_in_table(local_table, func.value->str)==0){
        fprintf(stderr, "Varianle \"%s\" used before definition\n", func.value->str);
        error_handler(3);
      }
    }
  }
  else{
  }
}


tToken scope_check(tToken scope, Symtable *global_table, Symtable *func_table){
  if(scope.type == t_keyword){
    if(((strcmp(scope.value->str, "for")==0)||(strcmp(scope.value->str, "if")==0)||(strcmp(scope.value->str, "else")==0))){


        Symtable scope_table;
        table_init(&scope_table);
        copy_table(func_table, &scope_table);

        set_redef_flag(&scope_table, 0);

        table_data def;
        def.type = id;
        def.defined = true;
        def.redef_flag = 0;
        table_insert(&scope_table, def, "_");

        while(scope.type != t_curlr){


          id_check(scope, &scope_table, global_table);
          //print_table(&scope_table);

          scope = *scope.next;
          scope = scope_check(scope, global_table, &scope_table);
        }
        if(DEBUG){printf("SCOPE TABLE\n");}
        if(DEBUG){print_table(&scope_table);}
        if(DEBUG){ printf("exiting scope\n");}
        if(DEBUG){printf("-------------\n");}
        destroy_table(&scope_table);
      }

    }

return scope;
}

//  -------------------------------------------------------------- //



//  -----------------------OTHER SUPPORT STUFF-------------------------------------- //

// Dealocation of everything //
// Punch al filthy mallocs

void senor_clean_fist(Symtable *table, synt_stack stack, tList token_list){

  tToken *temp = token_list.first;
  tToken *point;

  while(temp->type != 7){
    point = temp->next;
    dynamic_string *string = temp->value;
  //  free(string);
  //free(point);
    free(temp);
    temp = point;
  }
  destroy_table(table);
  stack_remove(&stack);
}

void print_stack(synt_stack stack){

    printf("PRINTING STACK\n");

    for(int i = 0; i < 10; i++){
      printf("%d\n", (stack->t[(stack->top)-i].type));
    }


      printf("----------------\n\n");

}

bool is_correct_kword(char* id, int which[20], int used){

  const char* K[] = {"empty", "package", "if","else", "for",
  "float64","func","int","return","string","inputs",
  "inputi","inputf","print","int2float","float2int",
  "len","substr","ord","chr"};

  for(int i = 0; i < used; i++){

      if(strcmp(id, K[which[i]])==0){
        return true;
    }
  }
  return false;
}

bool is_fce(char *id, Symtable *table){
  if(is_in_table(table, id)==1){
    Sym_table_item *temp;
    temp = search_in_table(table, id);
    if(temp->data.type == 1){
      return true;
    }
  }
  return false;
}

bool is_defined(char *id, Symtable *table){
  if(is_in_table(table, id)==1){
    Sym_table_item *temp;
    temp = search_in_table(table, id);
    if(temp->data.defined == true){
      return true;
    }
  }
  return false;

}



bool is_predefined(char *id, Symtable *table){
  if(is_in_table(table, id)==1){
    Sym_table_item *temp;
    temp = search_in_table(table, id);
    if(temp->data.predefined == true){
      return true;
    }
  }
  return false;

}
