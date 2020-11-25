/**
 * @file codegen.c
 *
 * Hlavní funkce pro generování kódu
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */

 #define _GNU_SOURCE
 #include "codegen.h"

psa_stack name_stack;
Symtable gen_table;

int scope_lvl = 0;
int in_for = 0;


int generate_code(tList list, Symtable *table){
  if(DEBUG){printf("\n----GENERATING CODE----\n\n");}

  table_init(&gen_table);
  copy_table(table, &gen_table);

  tToken token = (*list.first); // First token of program

  main_code(); // generate base code
  char* current_fce;


// stuff needed to solve nested if/else //
  int label_count = 0;
  int bra_cnt = 0;
  int if_flag = 0;
  int else_flag = 0;
  bool is_end = false;


  psa_stack stack;
  PSA_term term;

  ps_stack_init(&stack);
  ps_stack_init(&name_stack);
// -----------------------------------//

// stuff needed to solve nested for //



// -----------------------------------//


// stuff needed to solve redefinition inside scope //



// -----------------------------------//
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

      if((bra_cnt != 0)&&(token.type == t_curlr)&&(if_flag&&else_flag&&is_end)&&(stack->t[(stack->top)].type == type_if)){

        printf("LABEL IF$END$%d\n",  stack->t[(stack->top)].id);
        ps_stack_pop(stack);
        ps_stack_pop(name_stack);
        bra_cnt--;
        if_flag--;
        else_flag--;
        is_end = false;
        scope_lvl--;
        set_level_flag(&gen_table, scope_lvl);

      }else if((bra_cnt != 0)&&(token.type == t_curlr)&&(in_for)&&(stack->t[(stack->top)].type == type_for)){
        printf("JUMP FOR$BEGIN%d\n",  stack->t[(stack->top)].id);
        printf("LABEL FOR$END$%d\n",  stack->t[(stack->top)].id);
        scope_lvl=scope_lvl-2;
        ps_stack_pop(stack);
        ps_stack_pop(name_stack);
        bra_cnt--;
        in_for--;
        is_end = true;
        //print_table(&gen_table);
        set_level_flag(&gen_table, scope_lvl);
        //print_table(&gen_table);
        //printf("bra_cnt %d if_flag %d else_flag %d is_end %d\n", bra_cnt, if_flag, else_flag, is_end);
      }

// ASSIGN or DEF to id

      else if(token.type == t_id){

          id_solver(token, table, 0, stack);

      }
      else if((token.type == t_keyword)||((*token.next).type == t_keyword)){
        if(strcmp(token.value->str, "func")==0){
          printf("JUMP END%s$\n", (*token.next).value->str);
          printf("LABEL %s$\n", (*token.next).value->str);
          printf("CREATEFRAME\n");
          printf("PUSHFRAME\n");
          printf("DEFVAR LF@_\n");
          function_start(table, token);
          current_fce = (*token.next).value->str;
      }

    // -------------CREATING FRAMES FOR SCOPES OR FUNCTIONS---------------- //
      else if(strcmp(token.value->str, "for")==0){
        label_count++;
        bra_cnt++;
        is_end = false;
        in_for++;
        scope_lvl++;



        term.id = label_count;
        term.type = type_for;
        ps_stack_push(stack, term);
        ps_stack_push(name_stack, term);

        for_id_definer(token, &gen_table, table);



        token = *token.next;

        // solving or skiping definiton in the begining //
        if(token.type == t_semico){

        }else if(token.type == t_id){
          id_solver(token, table, 0, stack);
          while(token.type != t_semico){
            token = *token.next;
          }
        }
        token = *token.next; // skipping semico token
      // --------------------------------------------- //

      tToken after_assign = token;
      printf("JUMP FOR$START%d\n", stack->t[(stack->top)].id);

      printf("LABEL FOR$BEGIN%d\n",  stack->t[(stack->top)].id);

      while(after_assign.type != t_semico){
        after_assign = *after_assign.next;
      }
      after_assign = *after_assign.next; // skipping semico token

      if(after_assign.type != t_curll){
        id_solver(after_assign, table, 0, stack);
      }

      // -------------Solving condition --------------- //

      //init label//

      printf("LABEL FOR$START%d\n", stack->t[(stack->top)].id);

      expr_generator(token); // left side of condition
      printf("PUSHS TF@$$retval\n");

      expr_generator(*(*token.next).next);
      printf("PUSHS TF@$$retval\n"); // right side of condition

      rela_parser(*token.next);
      printf("DEFVAR TF@$$relation\n");
      printf("POPS TF@$$relation\n");

      printf("JUMPIFNEQ FOR$END$%d TF@$$relation bool@true\n",stack->t[(stack->top)].id);

      scope_lvl++;




      // --------------------------------------------- //

      }
      else if(strcmp((*token.next).value->str, "else")==0){

        printf("JUMP IF$END$%d\n", stack->t[(stack->top)].id);
        scope_lvl--;
        set_level_flag(&gen_table, scope_lvl);

        printf("\nLABEL IF$FALSE$%d\n", stack->t[(stack->top)].id);
        bra_cnt++;
        else_flag++;
        is_end = true;


        // some stuff to destroy local variables
        scope_lvl++;

      }
      else if(strcmp(token.value->str, "if")==0){
        label_count++;
        if_flag++;
        is_end = false;
        scope_lvl++;

        term.id = label_count;
        term.type = type_if;
        ps_stack_push(stack, term);
        ps_stack_push(name_stack, term);

        expr_generator(*token.next); // left side of condition
        printf("PUSHS TF@$$retval\n");

        expr_generator(*(*(*token.next).next).next);
        printf("PUSHS TF@$$retval\n"); // right side of condition

        rela_parser(*(*token.next).next);
        printf("DEFVAR TF@$$relation\n");
        printf("POPS TF@$$relation\n");
        printf("JUMPIFNEQ IF$FALSE$%d TF@$$relation bool@true\n",stack->t[(stack->top)].id);




        //printf("CREATEFRAME\n");
        //expr_generator(token);

      }
      else if(strcmp(token.value->str, "return")==0){
          if( (*(*token.next).next).type == t_comma ){
            multi_solver(*token.next, table, 0);
          }else{
            expr_generator(*token.next);
            printf("MOVE GF@$$retval0 TF@$$retval\n");

          }
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
destroy_table(&gen_table);
ps_stack_remove(&stack);
ps_stack_remove(&name_stack);
return 0;
}



char *id_mannager(tToken token){
  char *retval = "";
  if(name_stack->top > 1){
    //printf("%d scope level, name %s\n", scope_lvl, token.value->str);

    Sym_table_item *temp;
    temp = search_in_table(&gen_table, token.value->str);
    if(temp->data.level_flag == 0){
      asprintf(&retval, "%s ", token.value->str);

    }else if(temp->data.level_flag==scope_lvl){
      asprintf(&retval, "%s$%d ", token.value->str, name_stack->t[(name_stack->top)].id);
    }else{
      asprintf(&retval, "%s$%d ", token.value->str, temp->data.level_flag);
    }

  }else{
    asprintf(&retval, "%s ", token.value->str);
  }

  return retval;

}

void id_solver(tToken token, Symtable *table, int rekurze_cnt, psa_stack stack){
  //print_token(token);

  if((*token.next).type == t_def){
    if(in_for == 0){
      if(stack->top > 1){
        if((stack->t[(stack->top)].type == type_for)||(stack->t[(stack->top)].type == type_if)){

          set_level_flag_by_id(&gen_table, token.value->str, scope_lvl);

          printf("DEFVAR LF@%s$%d\n", token.value->str, stack->t[(stack->top)].id);
          generate_params(token, table, 0); // solve expr or function call
        }
      }else{

        printf("DEFVAR LF@%s\n",token.value->str);
        generate_params(token, table, 0); // solve expr or function call


      }
    }


  }else if((*token.next).type == t_assign){
    generate_params(token, table, rekurze_cnt); // solve expr or function call


  }else if((*token.next).type == t_comma){
    id_solver((*(*token.next).next), table, rekurze_cnt+1, stack);
    printf("MOVE LF@%s GF@$$retval%d\n", id_mannager(token), rekurze_cnt);
  }
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

void generate_params(tToken token, Symtable *table, int rekurze_cnt){
  char *name = token.value->str;
  tToken tname = token;


  token = *token.next; // Skip name
  token = *token.next; // skip assign or equal




  if((*token.next).type == t_comma){

    multi_solver(token, table, 0);
    printf("MOVE LF@%s GF@$$retval%d\n", id_mannager(tname), rekurze_cnt);
    return;
  }


  if(is_fce(token.value->str, table)){
    printf("CREATEFRAME\n");
    call_params(token);
    printf("CALL %s$\n", token.value->str);

    if(strcmp(name, "_")!=0){
      printf("MOVE LF@%s GF@$$retval%d\n", id_mannager(tname), rekurze_cnt);
    }

    return;
  }else{

    multi_solver(token, table, 0);
    printf("MOVE LF@%s GF@$$retval%d\n", id_mannager(tname), rekurze_cnt);

  }

}






//--------------------------------------------//

void expr_generator(tToken token){

  bool concat = concat_check(token);

  if(!concat){
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@$$retval\n");
    printf("\n");
    psa(token, 1);
    printf("\n");
    printf("POPS TF@$$retval\n");
  }
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
      printf("PUSHS %s\n", stringToInterpret(token.value->str));
    } else if(token.type == t_float){
      printf("PUSHS FLOAT@%s\n",token.value->str);
    }
    token = *token.next;
  }
}

//--------------------------------------------//

void multi_solver(tToken token, Symtable *table, int rekurze_cnt){



  bool comma_flag = 0;
  tToken tmp = token;
  while(tmp.type != t_eol){

    if(tmp.type == t_comma){
      comma_flag = 1;
      tmp = *tmp.next;
      break;
    }


    tmp = *tmp.next;
  }

//print_token(token);
//(*token.next).type == t_comma

  if(comma_flag){

    multi_solver(tmp, table, rekurze_cnt+1);
  }
  expr_generator(token);
  printf("MOVE GF@$$retval%d TF@$$retval\n\n", rekurze_cnt);
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

void rela_parser(tToken token){

  if(!strcmp(token.value->str, "<")){
    printf("LTS\n");

  }else if(!strcmp(token.value->str, ">")){
    printf("GTS\n");
  }else if(!strcmp(token.value->str, "==")){

    printf("EQS\n");

  }else if(token.type == t_neq){

    printf("EQS\n");
    printf("NOTS\n");

  }else if(!strcmp(token.value->str, "<=")){
    printf("DEFVAR TF@tmp1\n");
    printf("DEFVAR TF@tmp2\n");
    printf("POPS TF@tmp2\n");
    printf("POPS TF@tmp1\n");

    printf("PUSHS TF@tmp1\n");
    printf("PUSHS TF@tmp2\n");
    printf("LTS\n");

    printf("PUSHS TF@tmp1\n");
    printf("PUSHS TF@tmp2\n");
    printf("EQS\n");
    printf("ORS\n");

    printf("CREATEFRAME\n");

  }else if(!strcmp(token.value->str, ">=")){
    printf("DEFVAR TF@tmp1\n");
    printf("DEFVAR TF@tmp2\n");
    printf("POPS TF@tmp2\n");
    printf("POPS TF@tmp1\n");

    printf("PUSHS TF@tmp1\n");
    printf("PUSHS TF@tmp2\n");
    printf("GTS\n");

    printf("PUSHS TF@tmp1\n");
    printf("PUSHS TF@tmp2\n");
    printf("EQS\n");
    printf("ORS\n");

    printf("CREATEFRAME\n");



  }
}
//--------------------------------------------//



void type_print(tToken token){
  if(token.type == t_id){
    printf("LF@%s ", token.value->str);
  }else if(token.type == t_string){
    printf("%s\n", stringToInterpret(token.value->str));
  }


}

bool concat_check(tToken token){

  if((token.type == t_string) || ((*(*token.next).next).type== t_string)){

    if((*token.next).type == t_plus){
      printf("CREATEFRAME\n");
      printf("DEFVAR TF@$$retval\n");
      printf("CONCAT TF@$$retval ");
      type_print(token);
      type_print(*(*token.next).next);
      printf("\n");

    return true;
    }
  }
  return false;
}
//--------------------------------------------//


void for_id_definer(tToken token, Symtable *get_table, Symtable *table){

  int for_bra_cnt = 1;
  tToken temp = token;
  int for_scope_lvl  = scope_lvl;



  while(temp.type != t_eol){

    if((*temp.next).type == t_def){

      set_level_flag_by_id(&gen_table, temp.value->str, for_scope_lvl);

      printf("DEFVAR LF@%s$%d\n", temp.value->str, name_stack->t[(name_stack->top)].id);
      generate_params(temp, table, 0); // solve expr or function call
    }


  //  print_token(temp);

    temp = *temp.next;
  }

  //for_scope_lvl++;

  while(for_bra_cnt != 0){


    if((*temp.next).type == t_def){

      set_level_flag_by_id(&gen_table, temp.value->str, for_scope_lvl);

      printf("DEFVAR LF@%s$%d\n", temp.value->str, for_scope_lvl);
      generate_params(temp, table, 0); // solve expr or function call
    }
    else if(temp.type == t_keyword){
      if(!strcmp(temp.value->str, "if")){
        break;
      }
    }




    if(temp.type == t_curll){
      for_bra_cnt++;
    }else if(temp.type == t_curlr){
      for_bra_cnt--;
    }
    temp = *temp.next;
  }


}


//--------------------------------------------//
void f_print(tToken token){
  while(token.type!=t_eol){

    if(token.type == t_id){
      printf("WRITE LF@%s\n", id_mannager(token));

    }else if(token.type == t_string){
      printf("WRITE %s\n", stringToInterpret(token.value->str));
    }else if(token.type == t_float){
      printf("WRITE %s\n", float_to_ifj(token.value->str));
    }else if(token.type == t_number){
      printf("WRITE %s\n", int_to_ifj(token.value->str));
    }
    token = *token.next;
  }
}
//--------------------------------------------//
