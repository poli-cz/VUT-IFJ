 #include "PSA.h"




 static char prec_table[12][12] =
 {
 //   +     -    *     /     R     (     )      id  int float str  $
  	{ '>','>', '<' , '<' , '<' , '<' , '>' , '<', '<', '<', '<', '>' }, /// +
    { '>','>', '<' , '<' , '<' , '<' , '>' , '<', '<', '<', '<', '>' }, /// -
  	{ '>','>', '>' , '>' , '>' , '<' , '>' , '<', '<', '<', '<', '>' }, /// */ -- MUL
  	{ '>','>', '<' , '>' , '>' , '<' , '>' , '<', '<', '<', '<', '>' }, /// \ / -- div
  	{ '<','<', '<' , '<' , ' ' , '<' , '>' , '<', '<', '<', '<', '>' }, /// r (realtion operators) = <> <= < >= >
  	{ '<','<', '<' , '<' , '<' , '<' , '=' , '<', '<', '<', '<', 'x' }, /// (
  	{ '>','>', '>' , '>' , '>' , '=' , '>' , ' ', ' ', ' ', ' ', '>' }, /// )
    { '>','>', '>' , '>' , '>' , ' ' , '>' , ' ', ' ', ' ', ' ', '>' }, /// pid
  	{ '>','>', '>' , '>' , '>' , ' ' , '>' , ' ', ' ', ' ', ' ', '>' }, /// int
    { '>','>', '>' , '>' , '>' , ' ' , '>' , ' ', ' ', ' ', ' ', '>' }, /// float
    { '>','>', '>' , '>' , '>' , ' ' , '>' , ' ', ' ', ' ', ' ', '>' }, /// str
  	{ '<','<', '<' , '<' , '<' , '<' , 'x' , '<', '<', '<', '<', 'x' }  /// $
  };



  Prec_table_sym token_to_table(tToken token, bool generate){

    switch (token.type) {

      case t_plus:
          return plus;
      break;

      case t_minus:
          return minus;
      break;

      case t_mul:
          return mul;
      break;

      case t_div:
          return ddiv;
      break;

      case t_lbra:
          return l_bra;
      break;

      case t_rbra:
          return r_bra;
      break;

      case t_id:

          if(generate){
            printf("PUSHS LF@%s\n", id_mannager(token));
          }
          return pid;
      break;

      case t_number:
          if(generate){printf("PUSHS int@%s\n", token.value->str);}
          return pint;
      break;

      case t_float:
          if(generate){printf("PUSHS %s\n", float_to_ifj(token.value->str));}
          return pfloat;
      break;

      case t_string:
        if(generate){printf("PUSHS %s\n", stringToInterpret(token.value->str));}

          return pstring;
      break;

      default:
       if((token.type == 14)||(token.type == 27)||(token.type == 26)){
         if(generate){return dolar;}
         return rela;
       }
       else{
         if((token.type == t_colon)){
           fprintf(stderr, "Unexpected token\n");
           error_handler(1);
         }

         return dolar;
       }
      break;
       }
  }


int psa(tToken token, bool print_expr){
  if(DEBUG){printf("ENTERING PSA\n");}

  psa_stack stack;
  PSA_term term;
  term.sym = dolar;

  ps_stack_init(&stack);
  ps_stack_push(stack, term);


  bool success = false;

  do{
    if(DEBUG){print_token(token);}
    if(DEBUG){ps_print_stack(stack);}
    if(DEBUG){printf("%d\n", token_to_table(token, print_expr));}
    Prec_table_sym symtok = token_to_table(token, print_expr);
    switch (prec_table[get_stack_top(stack)][symtok]) {

      case '<':
        if(DEBUG){printf("shift\n");}

        if(DEBUG){ps_print_stack(stack);}
        term.sym = shift;

        int push_count = 0;

        data_type temp = stack->t[(stack->top)].data_type;

        while((stack->t[(stack->top)].sym)==final_E){
          push_count++;
          ps_stack_pop(stack);
        }

        ps_stack_push(stack, term);

        for (int i = 0; i < push_count; i++) {
          term.data_type = temp;
          term.sym = final_E;

          ps_stack_push(stack, term);
        }

      if(DEBUG){printf("after\n");}
      if(DEBUG){ps_print_stack(stack);}

        term.sym = symtok;
        ps_stack_push(stack, term);
        token = *token.next;
      break;

      case '>':
      if(DEBUG){printf("reduce\n");}
      if(DEBUG){printf("Sould move %d down\n", get_stack_top(stack));}
      if(DEBUG){ps_print_stack(stack);}
        reduce_rule(stack, print_expr);
      break;

      case '=':
        if(DEBUG){printf("equal\n");}
        term.sym = symtok;
        ps_stack_push(stack, term);
        if(DEBUG){ps_print_stack(stack);}
        token = *token.next;
      break;

      case 'x':
        if(DEBUG){ps_print_stack(stack);}
        if(DEBUG){printf("Should be empty stack\n");}
        if(DEBUG){printf("Exiting PSA\n");}
        ps_stack_remove(&stack);
        return 0;

      break;

      case ' ':

        fprintf(stderr, "bad expression syntax\n");
      return 5;
      break;
    }


  }while(!success);

  return 0;
}


void reduce_rule(psa_stack stack, int generate){

  int reduce_count = stack_shift_count(stack);
  //printf("%d\n", reduce_count);



  if(reduce_count == 1){

    reduce_by_rule(stack, 1, generate);

  }else if(reduce_count == 3){

    reduce_by_rule(stack, 3, generate);

  }else{
    fprintf(stderr, "Missing operand in expr\n");
    error_handler(5);
  }

}



void reduce_by_rule(psa_stack stack, int count, int generate){
  PSA_term term;


  switch (count) {
    case 1:

      term.sym = final_E;
      if((stack->t[(stack->top)].sym)==pid){
          ps_stack_pop(stack);
          ps_stack_pop(stack);
          term.data_type = type_NDEF;
      } else if((stack->t[(stack->top)].sym)==pint){
          ps_stack_pop(stack);
          ps_stack_pop(stack);
          term.data_type = type_int;

      } else if((stack->t[(stack->top)].sym)==pfloat){
          ps_stack_pop(stack);
          ps_stack_pop(stack);
          term.data_type = type_float64;
      } else if((stack->t[(stack->top)].sym)==pstring){
          ps_stack_pop(stack);
          ps_stack_pop(stack);
          term.data_type = type_string;
      }
      else{
        fprintf(stderr, "Expression id error\n");
        exit(5);
      }
      ps_stack_push(stack, term);
    break;

    case 3:
    if(DEBUG){printf("Rule for 3 tokens\n");}
    // -------- CHECK FOR RIGHT DATA TYPES ------------//
    if((stack->t[(stack->top)].sym) != r_bra){
      if((stack->t[(stack->top)-2].data_type)!=(stack->t[(stack->top)].data_type)){
        if((stack->t[(stack->top)-2].data_type)!=type_NDEF){
          if((stack->t[(stack->top)].data_type)!=type_NDEF){
            printf("Comparing %d with %d\n", (stack->t[(stack->top)-2].data_type), (stack->t[(stack->top)].data_type));
            fprintf(stderr, "TOKEN TYPE ERROR\n");
            exit(5);
          }
        }
      }
    }





      if((stack->t[(stack->top)].sym) == r_bra){
        if((stack->t[(stack->top)-1].sym) == final_E){
          if((stack->t[(stack->top)-2].sym) == l_bra){
            term.sym = final_E;
            term.data_type = stack->t[(stack->top-1)].data_type;

            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);

            ps_stack_push(stack, term);
          }
        }
        else{
          fprintf(stderr, "Unknown operand\n");
          exit(5);
        }
      }
      else if((stack->t[(stack->top)].sym) == final_E){
        if((stack->t[(stack->top)-1].sym) == mul){
          if((stack->t[(stack->top)-2].sym) == final_E){
            term.sym = final_E;
            term.data_type = stack->t[(stack->top-2)].data_type;
            if(generate){printf("MULS\n");}
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);

            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }
        else if((stack->t[(stack->top)-1].sym) == ddiv){
          if((stack->t[(stack->top)-2].sym) == final_E){
            term.sym = final_E;
            term.data_type = stack->t[(stack->top-2)].data_type;
            if(generate){printf("IDIVS\n");}
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);

            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }
        else if( ( (stack->t[(stack->top)-1].sym) == plus) || ((stack->t[(stack->top)-1].sym) == minus)){
          if((stack->t[(stack->top)-2].sym) == final_E){
            term.sym = final_E;
            if((stack->t[(stack->top)-1].sym) == plus){
              if(generate){printf("ADDS\n");}
            }else{
              if(generate){printf("SUBS\n");}
            }

            term.data_type = stack->t[(stack->top-2)].data_type;

            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);

            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }
        else if((stack->t[(stack->top)-1].sym) == rela){
          if((stack->t[(stack->top)-2].sym) == final_E){
            term.sym = final_E;
            term.data_type = stack->t[(stack->top-2)].data_type;

            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);

            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }

        else{
          fprintf(stderr, "Unknown operator\n");
          exit(5);
        }
      }




    break;
  }







}

int stack_shift_count(psa_stack stack){
  for(int i = 0; i < stack->top; i++){
    if((stack->t[(stack->top)-i].sym)==shift){
      return i;
    }
  }
return 255;
}

int get_stack_top(psa_stack stack){
  for(int i = 0; i < stack->top; i++){
    if((stack->t[(stack->top)-i].sym)<shift){
      return stack->t[(stack->top)-i].sym;
    }
  }
  return 0;
}




void ps_stack_init(psa_stack *stack){
*stack = malloc(sizeof(struct PSAStack));

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


bool ps_stack_pop(psa_stack stack){
  if((stack->top) == 0){
  //  printf("empty stack\n");
    return false;
  }

  stack->top--;
  stack->last--;
  return true;
}

bool ps_stack_push(psa_stack stack, PSA_term term){
  if((stack->top)==(stack->size)){
    stack->size = stack->size + STACK_DEFAULT;
    stack->t = realloc(stack->t, stack->size * sizeof(PSA_term));
  }
  stack->top++;
  stack->t[stack->top] = term;
  stack->last++;
  return true;
}

void ps_stack_remove(psa_stack *stack){
  free((*stack)->t);
  free(*stack);
  *stack = NULL;
}


void ps_print_stack(psa_stack stack){

  printf("\nPRINTING PSA STACK\n");

  for(int i = 0; i < 4; i++){
    printf("%d ", (stack->t[(stack->top)-i].sym));
    if((stack->t[(stack->top)-i].sym)==final_E){
      printf("with data type: ");
      if((stack->t[(stack->top)-i].data_type == type_int)){
        printf("Int\n");
      }else if((stack->t[(stack->top)-i].data_type == type_float64)){
        printf("float\n");
      }else if((stack->t[(stack->top)-i].data_type == type_string)){
        printf("string\n");
      }else if((stack->t[(stack->top)-i].data_type == type_NDEF)){
        printf("NDEF\n");
      }
      else{
        printf("WHAT\n");
      }
    }
    else{printf("\n");}


  }


    printf("----------------\n\n");

}
