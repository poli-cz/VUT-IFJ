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
#include "basic.h"
#include "dynamic_string.h"

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


token_type get_token(){
  tToken token; // structure of token in scanner.h
  char sym; // curent char from stdin
  lex_state state = s_start;

  while(1){
     sym = getc(source_file);

    switch (state)
    {
    case s_start:
        if(sym==EOF){state=s_eof;}
        else if(sym=='\n' || sym=='\t' || sym=='\\'){state=s_eol;}
        else if(isspace(sym)){state=s_start;}
        else if(isdigit(sym)){state=s_number;}
        else if (sym=='+'){state=s_plus;}
        else if (sym=='-'){state=s_minus;}
        else if (sym=='*'){state=s_mul;}
        else if (sym==':'){state=s_colon;}
        else if (sym==';'){state=s_semico;}
        else if (sym==','){state=s_comma;}
        else if (sym=='>'){state=s_grt;}
        else if (sym=='<'){state=s_lst;} 
        else if (sym=='('){state=s_lbra;}
        else if (sym==')'){state=s_rbra;}
        else if (sym=='{'){state=s_curll;}
        else if (sym=='}'){state=s_curlr;}
        else if (sym=='/'){state=s_div;}
        else if (sym== '\"'){state=s_lslash;}
        else if (sym== '!'){state=s_fact;}
        else if (sym=='_'){state=s_id;}
        else state=s_error;
    case s_grt:
      if(sym=='=')
          return t_grteq;
      else ungetc(sym,source_file);
      break;
    case s_lst:
      if(sym=='=')
          return t_lste;
      else ungetc(sym,source_file);
    break;
    case s_fact:
      if(sym=='=')
        return t_neq;
      else ungetc(sym,source_file);
    break;
    case s_plus:
        return t_plus;
      ungetc(sym,source_file);      
    case s_minus:
          
    case s_div:
      if(sym == '/')
        state = s_linecom;
      if(sym== '*')
        state =s_blockcom;

    case s_linecom:
    if (sym == '\n' || sym == EOF) {
        ungetc(sym,source_file);
        state = s_start;
    }

    case s_blockcom:
                if(sym == EOF)
                    return s_error;
                else if(sym == '*')
                    state = s_endcom;
                break;
    case s_endcom:
        if(sym == EOF)
                    return s_error;
                else if(sym == '/'){
                    state = s_start;
                    resetToken();
                }
                else
                    state = s_blockcom;
                break;
          

    case s_lbra:
          return t_lbra;
    break;
    case s_rbra:
          return t_rbra;
    break;
    case s_curll:
          return t_curll;
    break;
    case s_curlr:
          return t_curlr;
    break;

    case s_number:
      if(isdigit(sym)){
        pushToken(sym);
       break;
      }
      else if (sym == '.') {
         add_char(sym,&token.value);
         state = s_float;
                }
      else if (sym == 'e' || sym == 'E') {
                    add_char(sym,token.value);
                    state = s_exp;
       }
    case s_float:
        if(isdigit(sym)){
           pushToken(sym);
           break;
        }
        else if (sym == 'e' || sym == 'E') {
         add_char(sym,(token.value));
         state = s_exp;
        }

    case s_lslash:

    case s_mul:

    case s_colon:


    case s_semico:
        ungetc(sym,source_file);
        return t_semico;
        
    case s_comma:
        ungetc(sym,source_file);
        return t_comma;

    case s_id:
    if(isdigit(sym) || isalpha(sym) || sym == '_'){
         pushToken(sym);
         break;
     }

    case s_error:
      printf("error");   
    break;
    default:
      break;
    }
  }
  // return(token);
}
