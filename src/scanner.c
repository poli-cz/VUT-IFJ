/*
 * Předmět  :   IFJ / IAL
 * Soubor   :   scanner.sym - lexikální analyzátor reprezentovaný konečným automatem
 * Projekt  :   Implementace překladače imperativního jazyka IFJ20
 * Tým č    :
 * Varianta :
 * Autor    : Jan Polišenský (xpolis04)
 */

#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

#define ERROR_FALSE 0
#define ERROR_TRUE 2

FILE *source_file;


const char* KEYWORDS[] = {"if","else", "for", "float64","func","int","return","string","inputs","inputi","inputf","print","int2float","float2int","len","substr","ord",
"chr"
};

int is_key_word(dynamic_string *string){
  for(int i=0;i<KEYWORD_NUM;i++){
     if(strcmp(KEYWORDS[i],string->str)==0)
        return ERROR_TRUE;
  };
 return ERROR_FALSE;
}


tToken get_token(){
  tToken token; // structure of token in scanner.h
  char sym; // curent char from stdin
  lex_state state = s_start;
   init_dynamc_string(&token.value); // inicializace attributu tokenu
   token.type = s_start; // inicializace typu tokenu: pocatecni stav

  while(1){
     sym = getchar();

    switch (state)
    {
    case s_start:
        if(sym==EOF){state=s_eof;}
        else if(sym=='\n' || sym=='\t' || sym=='\\'){state=s_eol;}
        
        else if(isspace(sym)){
          add_char(sym,&token.value);
          state=s_start;
        }
        else if(isdigit(sym)){
          add_char(sym,&token.value);
          state=s_number;
        }
        else if (sym=='+'){
          add_char(sym,&token.value);
          state=s_plus;
        }
        else if (sym=='-'){
          add_char(sym,&token.value);
          state=s_minus;
        }
        else if (sym=='*'){
          add_char(sym,&token.value);
          state=s_mul;
        }
        else if (sym==':'){
          add_char(sym,&token.value);
          state=s_colon;
        }
        else if (sym==';'){
          add_char(sym,&token.value);
          state=s_semico;
        }
        else if (sym==','){
          add_char(sym,&token.value);
          state=s_comma;}
        else if (sym=='>'){
          add_char(sym,&token.value);
          state=s_grt;
        }
        else if (sym=='<'){
          add_char(sym,&token.value);
          state=s_lst;
        } 
        else if (sym=='('){
          add_char(sym,&token.value);
          state=s_lbra;
        }
        else if (sym==')'){
          add_char(sym,&token.value);
          state=s_rbra;
        }
        else if (sym=='{'){
          add_char(sym,&token.value);
          state=s_curll;
        }
        else if (sym=='}'){
          add_char(sym,&token.value);
          state=s_curlr;
        }
        else if (sym=='/'){
          add_char(sym,&token.value);
          state=s_div;
        }
        else if (sym== '\"'){
          add_char(sym,&token.value);
          state=s_lslash;
        }
        else if (sym== '!'){
          state=s_fact;
          add_char(sym,&token.value);
          }
        else if (sym=='_'|| isalpha(sym)){
          add_char(sym,&token.value);
          state=s_id;
        }
        else if(sym=='"'){
          add_char(sym,&token.value);
          state=s_string;
        }        
        else {
        add_char(sym,&token.value);
        state=s_error;
        }
        break;
    
    case s_grt:
      if(sym=='='){
        add_char(sym,&token.value);
        state = s_meq;
      }
      else
      {  
        ungetc(sym,stdin);
        token.type = t_grt;
        return token;
      }
    break;

    case s_lst:
      if(sym=='='){
        add_char(sym,&token.value);
        state = s_lst;
      }
      else
      {  
        ungetc(sym,stdin);
        token.type = t_lst;
        return token;
      }
    break;

    case s_string:
     if (sym='"'){
       token.type=t_string;
       return token;
     }
     else if(sym == EOF ||sym == '\n'){
      token.type=t_error;
      return token;
     } 
     else
      add_char(sym,token.value);
    break;  

    case s_fact:
      if(sym=='=')
        state=s_neq;
      else ungetc(sym,source_file);
    break;

    case s_neq:
      add_char(sym,&token.value);
      token.type = t_neq;
      ungetc(sym,stdin);
      return token;
    break;

    case s_plus:

        add_char(sym,&token.value);
        token.type=t_plus;
        ungetc(sym,stdin); 
        return token;
    break;

    case s_minus:
          add_char(sym,&token.value);
          token.type=t_minus;
          ungetc(sym,stdin);
          return token;
    break;

    case s_div:
    add_char(sym,&token.value);
      if(sym == '/')
        state = s_linecom;
      if(sym== '*')
        state =s_blockcom;
    break;
    
    case s_linecom:
    if (sym == '\n' || sym == EOF) {
      ungetc(sym,source_file);
      state = s_start;
    }
    break;

    case s_blockcom:
      if(sym == EOF){
        token.type=t_error;
        return token;
      }
      else if(sym == '*')
        state = s_endcom;
    break;

    case s_endcom:

      if(sym == EOF){
        token.type=t_error;
        return token;
      }
      else if(sym == '/'){
        state = s_start;
      }
        else
        state = s_blockcom;
      break;
          

    case s_lbra:
      add_char(sym,&token.value);
      token.type=t_lbra;
      ungetc(sym,stdin);
      return token;
    break;

    case s_rbra:
      add_char(sym,&token.value);
      token.type=t_rbra;
      ungetc(sym,stdin);
      return token;
    break;

    case s_curll:
      add_char(sym,&token.value);
      token.type=t_curll;
      ungetc(sym,stdin);
      return token;
    break;

    case s_curlr:
      add_char(sym,&token.value);
      token.type=t_curlr;
      ungetc(sym,stdin);
      return token;      
    break;


    //integer
    case s_number:
      if(isdigit(sym)){
       add_char(sym,&token.value);
       state=s_number;
      }
      else if (sym == '.'){
         add_char(sym,&token.value);
         state = s_float;
      }
      else if (sym == 'e' || sym == 'E'){
        add_char(sym,&token.value);
        state = s_exp;
       }
      else{
        ungetc(sym,stdin);
        token.type=t_number;
      }
      break;

    //cislo desatina cast
    case s_floatpoint:
      if(isdigit(sym)){
        add_char(sym,&token.value);
        state=s_float;
      }
      else{
        ungetc(sym,stdin);
        state=s_error;
       }
    break;    

    case s_float:
      if(isdigit(sym)){
        add_char(sym,&token.value);
        state=s_float;
      }
      else if (sym == 'e' || sym == 'E') {
        add_char(sym,&token.value);
        state = s_exp;
      }
      else{
        ungetc(sym,stdin);
        token.type=t_float;
        return token;
      }     
    break;

    /*
    //exponencialna cast
    case s_exp:
    if(sym == '+' || sym == '-'){
      add_char(sym,&token.value);
    }
    else if(isdigit(sym)){
       add_char(sym,&token.value);
    }
    else if(isspace(sym)){
      ungetc(sym,source_file);
      return t_number;
    }
    break;


    case s_lslash:

    case s_mul:
                {
                    ungetc(sym,source_file);
                    return t_mul;
                }
                break;
*/
    case s_colon:
      add_char(sym,&token.value);
      ungetc(sym,stdin);
      token.type=t_colon;
      return token;
    break;

    case s_semico:
      add_char(sym,&token.value);
      ungetc(sym,stdin);
      token.type=t_semico;
      return token;
    break;
  
  
   case s_comma:
      add_char(sym,&token.value);
      ungetc(sym,stdin);
      token.type=t_comma;
      return token;
    break;
  
    case s_id:
    if(isdigit(sym) || isalpha(sym) || sym == '_'){
      add_char(sym,&token.value);
      state=s_id;   
    }
    //else if(sym == EOF)
    //                return s_error;
    break;

    case s_error:
        break;
  
    }  

  }
}
