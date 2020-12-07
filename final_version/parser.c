/**
 * @file parser.c
 *
 * Hlavní tělo celého překladače, implementace syntaktické a sémantické analýzy
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

#define _GNU_SOURCE
#include <stdbool.h>
#include "parser.h"
#include "PSA.h"
#include <stdio.h>


tList dispose;
Symtable g_table;
synt_stack stack;

int multival = 0;

/*
  Hlavní parsovací funkce
 */
int parser(){

  int pars_err = 0;

  table_init(&g_table);
  stack_init(&stack, pars_err);

// semantic prerun, only check for some basic semantic actions
  tList pre = syntactic_prerun(&g_table);

    if(DEBUG){printf("\n--------SYNTAX CHECK-------\n");}

    dispose = pre;
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
    }

    if(DEBUG){printf("\n----CHECKS OK----\n\n");}


    err = generate_code(pre, &g_table);
  if(err != 0){
    senor_clean_fist(&g_table, stack, pre);
    error_handler(err);
  }

  senor_clean_fist(&g_table, stack, pre);
return 0;
}








//------------------------------------------------------------------------------//
//  ------------------- Functions for work with synt_stack  ------------------- //


/*
 Comparing terminals on stack
 Also does other checks

 */
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
      fprintf(stderr, "Bad Keyword\n");
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
    error_handler(99);
    return;
  }
  (*stack)->top = 1;
  (*stack)->last = 0;


  (*stack)->t = malloc(STACK_DEFAULT * sizeof(T_term));
  if(!(*stack)->t){
    error_handler(99);
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
    ex_term.type = t_eol;
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
    else if(token.type == t_curlr){
      stack_pop(stack, err_code);// Destroy

    //  ex_term.type = t_curlr;
    //  stack_push(stack, ex_term, err_code);
    }
    else{
      fprintf(stderr, "UNEXPECTED IN function retvals\n");
      all_fresh();
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
      all_fresh();
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
      all_fresh();
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
    all_fresh();
    exit(99);
  }
}

//  -------------------------------------------------------------- //



//  -----------------------SEMANTIC STUFF-------------------------------------- //

int semantic_check(Symtable *table, synt_stack stack, tList list, int err_code){
  if(DEBUG){printf("\n-----------SEMANTIC CHECK----------\n" );}


  tToken token = (*list.first);



  while(token.type != 7){

    // 1) Call without definition
    if(((token.type == t_keyword)||(token.type == t_id))&&((*token.next).type == t_lbra)){
      if(is_fce(token.value->str ,table)){
        if(is_defined(token.value->str ,table)==0){
          fprintf(stderr, "FUNCTION %s NOT DEFINED\n", token.value->str);
          return 3;
        }
        else{
          if(check_ok_params(table, token.value->str, token)!=0){
            fprintf(stderr, "FUNCTION %s BAD PARAMS\n", token.value->str);
            return 3;
          }
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

      parse_fc_params(&local_table, func);

      if(DEBUG){printf("BUILDED LOCAL FRAME for %s\n", func_name);}
      if(DEBUG){printf("------------------------------\n");}

      while(fce_end){

        func_call_checker(&local_table, func);
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

        if(fce_end == 0){
          break;
        }else{
          func = *func.next;
        }
      }
      if(DEBUG){print_table(&local_table);}
      //print_table(&local_table);
      //exit(2);
      destroy_table(&local_table);
    }
//-----------------------END LOCAL FRAME----------------------//

// --------------- CHECKING VARIABLE VALUES AND DATA TYPES ----------- //






  //print_token(token);

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

          get_data_type(local_table, func); // add here insert


          if(DEBUG){printf("Variable %s redefined in scope to value: ", func.value->str);}

        }
        else{
          if(is_defined(func.value->str, local_table)){
            fprintf(stderr, "Variable %s redefined\n", func.value->str);
            all_fresh();
            destroy_table(table);
            error_handler(3);

          }
          else{

          table_data iD;
          iD.d_type = get_data_type(local_table, func);
          iD.type = id;
          iD.defined = true;
          iD.redef_flag = 1;
          table_insert(local_table, iD, func.value->str);

          }
        }
    }
    else{


      table_data iD;
      iD.d_type = get_data_type(local_table, func);
      iD.type = id;
      iD.defined = true;
      iD.redef_flag = 1;
      table_insert(local_table, iD, func.value->str);


      tToken temp = func;
      bool for_flag = false;

      while(temp.type != t_eol){
        if(temp.type == t_semico){
          for_flag = true;
        }
        if(temp.type == t_eof){
          fprintf(stderr, "Unexpected EOF\n");
          exit(2);
        }
        temp = *temp.next;
      }

      if(for_flag){
        set_redef_flag_by_id(local_table, func.value->str, 0);
      }





    }

      tToken call = *func.next;
      call = *call.next;


    }else if((*func.next).type == t_assign){

      if(multival){
        check_multi_def(local_table, (*func.next));


      }else if(is_in_table(local_table, func.value->str)==0){
        fprintf(stderr, "Varianle \"%s\" used before definition\n", func.value->str);
        error_handler(3);
      }
      else if(is_fce((*(*func.next).next).value->str, &g_table)){

        check_retvals(local_table, func);
      }
      else{
        check_data_type(local_table, func);
      }


  }else if((*func.next).type == t_comma){
      multi_checker(local_table, func);
    }
  }
}


tToken scope_check(tToken scope, Symtable *global_table, Symtable *func_table){
  if(scope.type == t_keyword){
    if(((strcmp(scope.value->str, "for")==0)||(strcmp(scope.value->str, "if")==0)||(strcmp(scope.value->str, "else")==0))){

      if(strcmp(scope.value->str, "else")==0){  //  TRASH
        return *scope.next;                     //  SOLVE
      }                                         //



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
          func_call_checker(&scope_table, scope);

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
    free_string(&temp->value);
    free(temp);
    temp = point;
  }
  free_string(&point->value);
  free(point);

  destroy_table(table);
  stack_remove(&stack);
}

void all_fresh(){

  tToken *temp = dispose.first;
  tToken *point;

  while(temp->type != 7){
    point = temp->next;
    free_string(&temp->value);
    free(temp);
    temp = point;
  }
  free_string(&point->value);
  free(point);

  destroy_table(&g_table);
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

bool check_ok_params(Symtable  *table, char* func, tToken token){
  tToken def_check = token;
    bool prototype = 0;

  while(def_check.type != t_eol){

      if(def_check.type == t_curll){
        prototype = 1;
      }
      def_check = *def_check.next;
  }

  if(!prototype){
    Sym_table_item *temp;
    int param_count = 0;
    int expected = 0;


    if(!strcmp(token.value->str, "print")){

      return 0;
    }

    temp = search_in_table(table, token.value->str);
    char *params = temp->data.params;



// params count //
    char p = params[0];

    expected = atoi(&p);
    //printf("%d\n", expected);

// skip function name and assign mark //
    token = *token.next;
    token = *token.next;

    tToken last;
    while(token.type != t_rbra){

      if(last.type == token.type){
        if(token.type == t_comma){
          fprintf(stderr, "UNEXPECTED COMMA\n");
          return 1;
        }
      }

      if(token.type != t_comma){

        param_count++;
        last = token;
      }else if((*token.next).type == t_rbra){
          fprintf(stderr, "UNEXPECTED COMMA\n");
          return 1;

        }else{
          last = token;
        }
        token = *token.next;
      }

      if(expected == param_count){
        return 0;
      }else{
        return 1;
      }
    }
    else{
      return 0;
    }
}


data_type get_data_type(Symtable *table, tToken token){


  token = *token.next;

  if(token.type != t_def){
    fprintf(stderr, "Expeting definition, but Im just program not a cop\n");
    all_fresh();
    exit(3);
  }

  token_type arg_type = t_error; // store type of expression
  data_type arg_value = type_NDEF;

  while(token.type != t_eol){

    if(arg_type == t_error){
      if(token.type == t_string){
        arg_type = t_string;
        arg_value = type_string;
      }else if(token.type == t_number){
        arg_type = t_number;
        arg_value = type_int;
      }else if(token.type == t_float){
        arg_type = t_float;
        arg_value = type_float64;
      }
    }

    if(token.type == t_id){
      Sym_table_item *temp;

      temp = search_in_table(table, token.value->str);
      if(temp!=NULL){
        if(arg_type != t_error){
          if(temp->data.d_type != arg_value){
            fprintf(stderr, "Variable data type mismatch\n");
            all_fresh();
            exit(3);
          }
        }
      }
      else{
        fprintf(stderr, "Undefined variable in expresion\n");
        all_fresh();
        exit(3);
      }


    }

    if((token.type == t_number)||(token.type == t_float)||(token.type == t_string)){
      if(token.type != arg_type){
        printf("EXPR ANDVANCED ERR\n");
        all_fresh();
        exit(3);
      }

    }

    if(token.type == t_eof){
      fprintf(stderr, "Unexpected EOF\n");
    }
    else{
      token = *token.next;
    }

    if(token.type == t_semico){
      break; // if we are in for or if definition
    }
  }


  if(DEBUG){printf("-------------\n");}
  if(DEBUG){printf("EXITING TYPE CHECKER with %d\n", arg_type);}

  if(arg_type == t_number){
    return 1;
  }else if(arg_type == t_float){
    return 2;
  }else if(arg_type == t_string){
    return 3;
  }
  else{
    //printf("%d\n", arg_type);
    //printf("WE ARE ALL DOMED\n");
  }

  return type_NDEF;
}



void parse_fc_params(Symtable *table, tToken token){


  while(token.type!=t_rbra){

    if(token.type == t_id){
      table_data def;
      def.type = id;
      def.defined = true;
      def.redef_flag = 0;
      //print_token(token);

      if(!strcmp((*token.next).value->str, "int")){
        def.d_type = type_int;
      }else if(!strcmp((*token.next).value->str, "float64")){

        def.d_type = type_float64;
      }else if(!strcmp((*token.next).value->str, "string")){
        def.d_type = type_string;
      }
      table_insert(table, def, token.value->str);
    }

    token = *token.next;
  }
}



void multi_checker (Symtable *table, tToken token){
  char *id = token.value->str;
  token = *token.next;


  while(token.type != t_eol){
  //  print_token(token);
    if(token.type == t_eof){
      break;
    }
    if(token.type == t_assign){
      if(!is_defined(id, table)){
        fprintf(stderr, "Variable %s not defined\n",id);
        exit(3);
      }
      multival++;
    }
    token = *token.next;
  }
}

void check_multi_def(Symtable *table, tToken token){
    int val_cnt = 0;
    if(DEBUG){printf("-----ENTERED MULTIVAL ASSIGN CHECK -----\n");}

    token = *token.next;

    if((token.type == t_id)||(token.type == t_keyword)){
      if(is_fce(token.value->str, &g_table)){
        if(DEBUG){printf("Check for correct funtion retvals\n");}

        multival = 0;
        return;
      }
    }


    while(token.type != t_eol){
      if(token.type == t_id){
        if(!is_defined(token.value->str, table)){
          fprintf(stderr, "Value %s in multiassign not defined\n",token.value->str);
          exit(7);
        }

      }
      if(token.type == t_comma){
        val_cnt++;
      }


      if(token.type == t_eof){
        fprintf(stderr, "UNEXPECTED EOF\n");
        exit(2);
      }
      token = *token.next;
    }

    if(val_cnt != multival){
      fprintf(stderr, "BAD multival assign\n");
      exit(7);
    }

    multival = 0;
}


void check_retvals(Symtable *table, tToken token){

  data_type var_type;
  char* retvals;
  Sym_table_item *temp;
  Sym_table_item *f_ret;



  temp = search_in_table(table, token.value->str);
  var_type = temp->data.d_type;

  f_ret = search_in_table(&g_table, (*(*token.next).next).value->str);
  retvals = f_ret->data.retvals;




  if(var_type == type_int){

    if(strcmp(retvals, "int ")!=0){
      printf("%s|%d\n",retvals,strcmp(retvals, "int "));
      fprintf(stderr, "Value of type INT not matched with function return type\n");
      exit(7);
    }
  }else if(var_type == type_string){
    if(strcmp(retvals, "string ")!=0){
      //printf("%s|%d\n",retvals,strcmp(retvals, "int "));
      fprintf(stderr, "Value of type STR not matched with function return type\n");
      exit(7);
    }
  }else if(var_type == type_float64){
    if(strcmp(retvals, "float64 ")!=0){
      //printf("%s|%d\n",retvals,strcmp(retvals, "int "));
      fprintf(stderr, "Value of type FLOAT not matched with function return type\n");
      exit(7);
    }
  }
}






void func_call_checker(Symtable *table, tToken token){

  if((token.type == t_id)||(token.type == t_keyword)){
  if(((token.type == t_id)||(token.type == t_keyword))&&((*token.next)).type == t_lbra){
    if(!strcmp(token.value->str, "if")||!strcmp(token.value->str, "for")||!strcmp(token.value->str, "else")){
      return;
    }


    char* name = token.value->str;


    if(!strcmp(name, "print")){
      check_print(table, token);
      return;
    }

    Sym_table_item *func_info;
    func_info = search_in_table(&g_table, token.value->str);

    char *f_params = func_info->data.params;

    char *params= "";
    int count = 0;

    token = *token.next;
    while(token.type != t_eol){
      if(token.type == t_number){
        if(-1 == asprintf(&params,"int %s", params)){
          fprintf(stderr, "internal\n");
          exit(99);
        }
        count++;
      }else if(token.type == t_string){
        if(-1 == asprintf(&params,"string %s", params)){
          fprintf(stderr, "internal\n");
          exit(99);
        }
        count++;
      }else if(token.type == t_float){
        if(-1 == asprintf(&params,"float64 %s", params)){
          fprintf(stderr, "internal\n");
          exit(99);
        }
        count++;
      }else if(token.type == t_id){

        if(!is_defined(token.value->str, table)){
          fprintf(stderr, "ID %s in function call undefined\n", token.value->str);
          exit(6);
        }else{
          Sym_table_item *temp;
          temp = search_in_table(table, token.value->str);
          data_type var_type = temp->data.d_type;


        //  printf("%d var_type\n", var_type);
          if(var_type == type_int){
            if(-1 == asprintf(&params,"int %s", params)){
              fprintf(stderr, "internal\n");
            }
          }else if(var_type == type_string){
            if(-1 == asprintf(&params,"string %s", params)){
              fprintf(stderr, "internal\n");
            }
          }else if(var_type  == type_float64){
            if(-1 == asprintf(&params,"float64 %s", params)){
              fprintf(stderr, "internal\n");
            }
          }
          count++;
        }
      }

      if(token.type == t_eof){
        fprintf(stderr, "Unexpected EOF\n");
        exit(2);
      }
      token = *token.next;
    }
    if(-1 == asprintf(&params,"%d %s",count, params)){
      fprintf(stderr, "internal\n");
    }
    if(DEBUG){printf("%s expected PARAMS\n", f_params);}
    if(DEBUG){printf("%s REAL PARAMS\n\n", params);}

    if(strcmp(params, f_params)){
      fprintf(stderr, "bad parameters for function %s\n", name);
      fprintf(stderr, "%s expected PARAMS\n", f_params);
      fprintf(stderr, "%s got PARAMS\n\n", params);
      exit(6);
    }
      }
    }
  }
void check_print(Symtable *table, tToken token){

  while(token.type != t_eol){
    if(token.type == t_id){
      if(!is_defined(token.value->str, table)){
        fprintf(stderr, "Id %s in printf call undefine\n",token.value->str);
        exit(3);
      }
    }

    if(token.type == t_eof){
      fprintf(stderr, "Unexpected eof in printf call\n");
      exit(2);
    }
    token = *token.next;
  }
}


void check_data_type(Symtable *table, tToken token){

  Sym_table_item *temp;

  temp = search_in_table(table, token.value->str);
  data_type var_type = temp->data.d_type;

  while(token.type != t_eol){


    if((token.type == t_number)||(token.type == t_string)||(token.type == t_float)){
      if(var_type == type_int){
        if(token.type != t_number){
          fprintf(stderr, "Bad types during assing\n");
          exit(5);
        }

      }else if(var_type == type_float64){
        if(token.type != t_float){
          fprintf(stderr, "Bad types during assing\n");
          exit(5);
        }
      }else if(var_type == type_string){
        if(token.type != t_string){
          fprintf(stderr, "Bad types during assing\n");
          exit(5);
        }
      }
    }





    token=*token.next;
  }












}
