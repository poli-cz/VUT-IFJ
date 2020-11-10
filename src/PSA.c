/**
 * @file PSA.c
 *
 * Implemntace Precedenční syntaktické analýzy pro zpracování výrazů
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

 #include "PSA.h"


int expr_parse(Symtable *table, synt_stack stack, tToken token ,int err_code){
  int skip_counter = 0; // count how many tokens we can skip
  int in_function;
  tToken previe = *token.next;

  int bracket_counter = 0;

  printf("----Entering PSA----\n");

  while(1){
    // Counting correct number of brackets //
    if(token.type == t_lbra){
      bracket_counter++;
      if(previe.type == t_rbra){
        printf("empty brackets\n");
        stack_remove(&stack);
        exit(3);

      }
    }
    else if(token.type == t_rbra){
      bracket_counter--;
    }










    if(token.type == t_number){
      tToken div;
      div = *token.next;
      if(div.type == t_div){
        div = *div.next;
        if((div.type == t_number)&&(strcmp(div.value->str, "0")==0)){
          printf("ZERO IN DIV\n" );
          exit(9);
        }
      }
    }




    /**
     *  If we are in function, by detecking n_call_param on stack we let one t_rbra ) because it needs to match
     *  Its quite dirty solution but it works, so... ok i gues..
     *
     */
    in_function = is_in_stack(stack, n_call_param);
    if((token.type == t_eol)||(token.type == t_curll)||(token.type == t_semico)||((token.type == t_rbra)&&(in_function))){


      if(in_function){
        if(bracket_counter!=-1){
          printf("bracket missmatch in lonely expr()\n");
          printf("%d\n", bracket_counter);
          stack_remove(&stack);
          exit(3);
        }

      }
      else{
        if(bracket_counter!=0){
          printf("bracket missmatch in expr\n");
          printf("%d\n", bracket_counter);
          stack_remove(&stack);
          exit(3);
        }
      }
      printf("----Exiting PSA----\n");
      return skip_counter;
    }
    skip_counter++;
    token = *token.next;
    previe = *previe.next;
  }
}
