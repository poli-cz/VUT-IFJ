/**
 * @file PSA.c
 *
 * Implementace preprocesoru pro Precedenční syntaktickou analýzu
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
  tToken first = token;



  int bracket_counter = 0;

  if(DEBUG){printf("----RUNNING PSA PRE-CHECKS----\n");}

  while(1){

    if(DEBUG){printf("PSA TOKEN");}
    if(DEBUG){print_token(previe);}
    if(previe.type == t_eof){
      fprintf(stderr, "Unexpected eof\n");
      exit(1);
    }
    // Counting correct number of brackets //
    if(token.type == t_lbra){
      bracket_counter++;
      if(previe.type == t_rbra){
        fprintf(stderr, "empty brackets\n");
        stack_remove(&stack);
        exit(2);

      }
    }
    else if(token.type == t_rbra){
      bracket_counter--;
    }















    if(DEBUG){printf("Is in table %d\n", is_in_table(table, token.value->str));}

    if(token.type == t_id){
      if(!is_predefined(token.value->str,table)){
        fprintf(stderr, "Undefined value in expression %s\n", token.value->str);
        exit(3);
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
          fprintf(stderr, "bracket missmatch in lonely expr\n");

          stack_remove(&stack);
          exit(2);
        }

      }
      else{
        if(bracket_counter!=0){
          fprintf(stderr, "bracket missmatch in expr\n");

          stack_remove(&stack);
          exit(2);
        }
      }
      if(DEBUG){printf("----Exiting PSA prerun----\n");}


      if(psa(first, 0)!=0){
        exit(5);
      }

      return skip_counter;
    }
    skip_counter++;
    token = *token.next;
    previe = *previe.next;
  }
}
