 #include "PSA.h"


 static char prec_table[8][8] =
 {
 //   +-    *     /     R     (     )     i     $
  	{ '>' , '<' , '<' , '<' , '<' , '>' , '<' , '>' }, /// +-
  	{ '>' , '>' , '>' , '>' , '<' , '>' , '<' , '>' }, /// */ -- MUL
  	{ '>' , '<' , '>' , '>' , '<' , '>' , '<' , '>' }, /// \ / -- div
  	{ '<' , '<' , '<' , ' ' , '<' , '>' , '<' , '>' }, /// r (realtion operators) = <> <= < >= >
  	{ '<' , '<' , '<' , '<' , '<' , '=' , '<' , 'x' }, /// (
  	{ '>' , '>' , '>' , '>' , '=' , '>' , ' ' , '>' }, /// )
  	{ '>' , '>' , '>' , '>' , ' ' , '>' , ' ' , '>' }, /// i (id, int, float64, string)
  	{ '<' , '<' , '<' , '<' , '<' , 'x' , '<' , 'x' }  /// $
  };



  Prec_table_sym token_to_table(tToken token){

    switch (token.type) {

      case t_plus: return 0; break;
      case t_minus: return 0; break;
      case t_mul: return 1; break;
      case t_div: return 2; break;
      case t_lbra: return 4; break;
      case t_rbra: return 5; break;
      case t_id: return 6; break;
      case t_number: return 6; break;
      case t_float: return 6; break;
      case t_string: return 6; break;

      default:
       if((token.type == 14)||(token.type == 27)||(token.type == 26)){
         return 3;
       }
       else{
         if((token.type == t_colon)){
           fprintf(stderr, "Unexpected token\n");
           error_handler(1);
         }

         return 7;
       }
      break;
       }
  }


int psa(tToken token){
//  printf("ENTERING PSA\n");

  psa_stack stack;
  PSA_term term;
  term.sym = dolar;

  ps_stack_init(&stack);
  ps_stack_push(stack, term);

  bool success = false;

  do{
  //  print_token(token);
  //  ps_print_stack(stack);
  //  printf("%d\n", token_to_table(token));
    Prec_table_sym symtok = token_to_table(token);
//  printf("%d stack top \n", get_stack_top(stack));
    switch (prec_table[get_stack_top(stack)][symtok]) {

      case '<':
  //      printf("shift\n");

    //    ps_print_stack(stack);
        term.sym = shift;

        int push_count = 0;

        while((stack->t[(stack->top)].sym)==final_E){

          push_count++;
          ps_stack_pop(stack);
        }

        ps_stack_push(stack, term);

        for (int i = 0; i < push_count; i++) {
          term.sym = final_E;
          ps_stack_push(stack, term);
        }

  //      printf("after\n");
  //      ps_print_stack(stack);

        term.sym = symtok;
        ps_stack_push(stack, term);
        token = *token.next;
      break;

      case '>':
  //      printf("reduce\n");
  //      printf("Sould move %d down\n", get_stack_top(stack));
    //    ps_print_stack(stack);
        reduce_rule(stack);
      break;

      case '=':
  //      printf("equal\n");
        term.sym = symtok;
        ps_stack_push(stack, term);
    //    ps_print_stack(stack);
        token = *token.next;
      break;

      case 'x':
    //    ps_print_stack(stack);
    //    printf("Should be empty stack\n");
        //exit(2);
        return 0;

      break;

      case ' ':

        fprintf(stderr, "bad expression syntax\n");
      return 5;
      break;
    }


  }while(!success);
}


void reduce_rule(psa_stack stack){

  int reduce_count = stack_shift_count(stack);
  //printf("%d\n", reduce_count);



  if(reduce_count == 1){

    reduce_by_rule(stack, 1);

  }else if(reduce_count == 3){

    reduce_by_rule(stack, 3);

  }else{
    fprintf(stderr, "Missing operand in expr\n");
    error_handler(5);
  }
}



void reduce_by_rule(psa_stack stack, int count){
  PSA_term term;

  switch (count) {
    case 1:
      if((stack->t[(stack->top)].sym)==iid){
        ps_stack_pop(stack);
        ps_stack_pop(stack);
        term.sym = final_E;
        ps_stack_push(stack, term);

      }
      else{
        fprintf(stderr, "Expression id error\n");
        exit(5);
      }

    break;

    case 3:
  //  printf("Rule for 3 tokens\n");
      if((stack->t[(stack->top)].sym) == r_bra){
        if((stack->t[(stack->top)-1].sym) == final_E){
          if((stack->t[(stack->top)-2].sym) == l_bra){
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            term.sym = final_E;
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
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            term.sym = final_E;
            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }
        else if((stack->t[(stack->top)-1].sym) == ddiv){
          if((stack->t[(stack->top)-2].sym) == final_E){
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            term.sym = final_E;
            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }
        else if((stack->t[(stack->top)-1].sym) == plus_minus){
          if((stack->t[(stack->top)-2].sym) == final_E){
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            term.sym = final_E;
            ps_stack_push(stack, term);
          }
          else{
            fprintf(stderr, "Unknown operand\n");
            exit(5);
          }
        }
        else if((stack->t[(stack->top)-1].sym) == rela){
          if((stack->t[(stack->top)-2].sym) == final_E){
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            ps_stack_pop(stack);
            term.sym = final_E;
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
}




void ps_stack_init(psa_stack *stack){
*stack = malloc(sizeof(struct PSAStack));

if(!(*stack)){

  return;
}
(*stack)->top = 1;
(*stack)->last = 0;


(*stack)->t = malloc(STACK_DEFAULT * sizeof(T_term));
  if(!(*stack)->t){
  //  fprintf(stderr, "UH stacky stack\n");
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
    printf("%d\n", (stack->t[(stack->top)-i].sym));
  }


    printf("----------------\n\n");

}
