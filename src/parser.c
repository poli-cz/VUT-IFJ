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



// Main parsing function
int parser(){

  int pars_err = 0;
  Symtable g_table;
  synt_stack stack;

  table_init(&g_table);
  stack_init(&stack, pars_err);



// semantic prerun, only check for some basic semantic actions
  tList pre = syntactic_prerun(&g_table);


    printf("\n--------SYNTAX CHECK-------\n");

    tToken s_tok = (*pre.first); // Token for syntax check
    T_term p_term;
    p_term.type = n_prog;  // Default non terminal

    stack_push(stack, p_term, pars_err);


  //  for(int i = 0; i < 40; i++){ // only for debug
    while(1){ // until EOF

      printf("-----------------\n");
      print_token(s_tok);
     printf("-----------------\n");
      print_stack(stack);

      if((stack->t[stack->top].type) > t_string){ // Non terminal on stack
        printf("EXPAND\n");
        stack_expand(&g_table, stack, s_tok, pars_err);
      }
      else{

        if(stack_compare(stack, s_tok) == true){
        //  printf("COMPARING OK\n");
          stack_pop(stack, pars_err);

// --------EMPTY STACK--- ANALYSIS--DONE-----------//
          if((stack->top==1)&&(s_tok.type == 7)){
            printf("\n-------------SYNTAX OK-------------\n");
            break;
          }
          else if((stack->top!=1)&&(s_tok.type == 7)){
            printf("unexpected EOF\n Returning error 3\n");
            senor_clean_fist(&g_table, stack);
            error_handler(3);
          }

//------------------------------------------------//

          semantic_check(&g_table, stack, s_tok, pars_err);
          s_tok = *s_tok.next;
        }
        else{
          printf("Syntax check failed\n");
          senor_clean_fist(&g_table, stack);
          error_handler(3);
        }
      }
    }

    printf("\n--------SEMANTIC CHECK-------\n");

/*  Some semantic checks are done in preprocesor and also in syntax
    Mainly checking for undefined functions and that kind of stuff

*/






return 0;
}


//------------------------------------------------------------------------------//
//  ------------------- Functions for work with synt_stack  ------------------- //



bool stack_compare(synt_stack stack, tToken token){
  printf("%d on  STACK\n", (stack->t[stack->top]).type);
  printf("%d is TOKEN\n", (token.type));


// ----- aditional check for Kword name -------//
  if((stack->t[stack->top]).k_check == true){
    bool ok = is_correct_kword(token.value->str, (stack->t[stack->top]).k_w, (stack->t[stack->top]).used);
    if(!ok){
      printf("Bad Keyword\n");
      return false;
    }
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
    printf("empty stack\n");
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

      ex_term.type = t_id;
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
    else{
      stack_pop(stack, err_code);// Destroy n_params_n

      ex_term.type = n_param_n;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_id;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_keyword;
      ex_term.k_w[0] = 5; // check for double
      ex_term.k_w[1] = 7; // check for int
      ex_term.k_w[2] = 9; // check for string
      ex_term.k_check = true;
      ex_term.used = 3;
      stack_push(stack, ex_term, err_code);
      ex_term.k_check = false;

  // --------------------------------------------------------------------//

    }
  }
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
  else if((stack->t[stack->top].type) == n_fretval){
    if(token.type == t_comma){
      ex_term.type = n_fretval;
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_expr;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_comma;
      stack_push(stack, ex_term, err_code);
    }
    else if(token.type == t_curll){
      stack_pop(stack, err_code);// Destroy
    }
  }




  else if((stack->t[stack->top].type) == n_body){
    if(token.type == t_eol){
      stack_pop(stack, err_code); // Destroy

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
      stack_push(stack, ex_term, err_code);
      }
    else if(token.type == t_keyword){
      stack_pop(stack, err_code); // Destroy
    }
    else if(token.type == t_curlr){
      stack_pop(stack, err_code); // Destroy
      }
    else if(token.type == t_number){
      stack_pop(stack, err_code); // Destroy

      ex_term.type = n_expr; // cal precedent analysis
      stack_push(stack, ex_term, err_code);

      ex_term.type = n_body;
      stack_push(stack, ex_term, err_code);

      ex_term.type = t_eol;
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
  }
  else if((stack->t[stack->top].type) == n_body_id){
      if(token.type == t_eq){
        stack_pop(stack, err_code);

        ex_term.type = n_body_id_var;
        stack_push(stack, ex_term, err_code);

        ex_term.type = t_eq;
        stack_push(stack, ex_term, err_code);
      }
      else if(token.type == t_assign){
        stack_pop(stack, err_code);

        ex_term.type = n_body_id_var;
        stack_push(stack, ex_term, err_code);

        ex_term.type = t_assign;
        stack_push(stack, ex_term, err_code);
      }
  }
  else if((stack->t[stack->top].type) == n_body_id_var){
      if(is_fce(token.value->str, table)==1){
        stack_pop(stack, err_code);

        ex_term.type = n_func_call;
        stack_push(stack, ex_term, err_code);
      }
      else{
        stack_pop(stack, err_code); // Destroy

        ex_term.type = n_expr; // cal precedent analysis
        stack_push(stack, ex_term, err_code);
      }
  }
  else if((stack->t[stack->top].type) == n_fretvals){
    if(token.type == t_curlr){
      stack_pop(stack, err_code);// Destroy
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
  else if((stack->t[stack->top].type) == n_expr){


    }
  }
}
// Dealocation of everything //

void senor_clean_fist(Symtable *table, synt_stack stack){
  destroy_table(table);
  stack_remove(&stack);
}


//  -------------------------------------------------------------- //



//  -----------------------SEMANTIC STUFF-------------------------------------- //

void semantic_check(Symtable *table, synt_stack stack, tToken token, int err_code){






















}




//  -------------------------------------------------------------- //



//  -----------------------OTHER SUPPORT STUFF-------------------------------------- //
void print_stack(synt_stack stack){

printf("PRINTING STACK\n");

      printf("%d\n", (stack->t[(stack->top)].type));
      printf("%d\n", (stack->t[stack->top-1].type));
      printf("%d\n", (stack->t[(stack->top)-2].type));
      printf("%d\n", (stack->t[(stack->top)-3].type));
      printf("%d\n", (stack->t[(stack->top)-4].type));
      printf("%d\n", (stack->t[(stack->top)-5].type));

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
