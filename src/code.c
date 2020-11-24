/**
 * @file code.c
 * 
 * Hlavní funkce pro generování kódu
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xstefe11> Nina Stefekova
 */

#include "codegen.h"


void main_code(){
  // base code generation
  printf(".IFJcode20\n\
  DEFVAR GF@$$retval0\n\
  DEFVAR GF@$$retval1\n\
  DEFVAR GF@$$retval2\n\
  DEFVAR GF@$$retval3\n\
  DEFVAR GF@$$retval4\n\
  DEFVAR GF@$$retval5\n\
  CREATEFRAME\n\
  PUSHFRAME\n\
  JUMP main$\n\
  \n");


//inputs
printf("LABEL inputs\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@$return\n");
printf("  READ LF@$return string\n");
printf("  MOVE GF@$$retval0 LF@$return\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");


//inputi
printf("  LABEL inputi\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@$return\n");
printf("  READ LF@$return int\n");
printf("  MOVE GF@$$retval0 LF@$return\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");

//inputf
printf("  LABEL inputf\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@$return\n");
printf("  READ LF@$return float\n");
printf("  MOVE GF@$$retval0 LF@$return\n");
printf("  POPFRAME\n");
printf("  RETURN\n\n");


//print
printf("LABEL print\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@n\n");
printf("  DEFVAR LF@tmp\n");
printf("  POPS LF@n\n");

printf("  LABEL print_loop\n");
printf("  POPS LF@tmp\n");
printf("  WRITE LF@tmp\n");
printf("  SUB LF@n LF@n int@1\n");
printf("  JUMPIFNEQ  print_loop LF@n nt@0\n");

printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");


//len
printf("LABEL len\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@s\n");
printf("  POPS LF@s\n");
printf("  DEFVAR LF@length\n");
printf("  STRLEN LF@length LF@s\n");
printf("  MOVE GF@$$retval0 LF@length\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");



//substr
printf("LABEL substr\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@s\n");
printf("  DEFVAR LF@i\n");
printf("  DEFVAR LF@n\n");
printf("  DEFVAR LF@s_length\n");
printf("  DEFVAR LF@s_condition\n");
printf("  DEFVAR LF@n_condition\n");
printf("  DEFVAR LF@tmp_string\n");
printf("  DEFVAR LF@sub_string\n");
printf("  DEFVAR LF@char\n");
printf("  DEFVAR LF@tmp_i\n");
printf("  POPS LF@n\n");
printf("  POPS LF@i\n");
printf("  POPS LF@s\n");
printf("  STRLEN LF@s_length LF@s\n");
printf("  GT LF@s_condition LF@i LF@s_length\n"); 
printf("  JUMPIFEQ SUB_LABEL_ERROR LF@s_condition bool@true\n");
printf("  LT LF@n_condition LF@n int@0\n"); 
printf("  JUMPIFEQ SUB_LABEL_ERROR LF@n_condition bool@true\n");

printf("  LT LF@s_condition LF@i int@0\n"); 
printf("  JUMPIFEQ SUB_LABEL_ERROR LF@s_condition bool@true\n");


printf("  LABEL SUB_LABEL_LOOP\n");
printf("  GETCHAR LF@char LF@s LF@i\n");
printf("  MOV LF@tmp_string LF@sub_string");
printf("  CONCAT LF@sub_string LF@tmp_string LF@char\n");
printf("  ADD LF@i LF@i int@1\n");
printf("  SUB LF@n  LF@n int@1\n");
printf("  JUMPIFNEQ  SUB_LABEL_LOOP LF@n  int@0\n");
printf("  MOV GF@$$retval0 LF@sub_string\n");
printf("  MOV GF@$$retval1 int@0\n");
printf("  JUMP SUB_LABEL_END\n");


printf("  LABEL SUB_LABEL_ERROR\n");
printf("  MOV GF@$$retval1 int@1\n");

printf("  LABEL SUB_LABEL_END\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");



//ord
printf("LABEL ord\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@s\n");
printf("  DEFVAR LF@i\n");
printf("  DEFVAR LF@lens\n");
printf("  DEFVAR LF@condition\n");
printf("  DEFVAR LF@char\n");
printf("  POPS LF@i\n");
printf("  POPS LF@s\n");
printf("  STRLEN LF@lens LF@s\n");
printf("  LT LF@condition LF@i  LF@lens\n");
printf("  JUMPIFNEQ ORD_LABEL_ERROR LF@condition bool@true\n");
printf("  STR2INT GF@$$retval0 LF@s LF@i\n");
printf("  MOV GF@$$retval1 int@0\n");
printf("  JUMP ORD_LABEL_END\n");
printf("  LABEL ORD_LABEL_ERROR\n");
printf("  MOV GF@$$retval1 int@1\n");
printf("  LABEL ORD_LABEL_END\n");
printf("  POPFRAME\n");
printf("  RETURN\n");


//chr
printf("LABEL chr\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@i\n");
printf("  POPS LF@i\n");
printf("  DEFVAR LF@conditionchr\n");
printf("  LT LF@conditionchr LF@i int@255\n");
printf("  JUMPIFNEQ CHR_LABEL_ERROR LF@conditionchr bool@true\n");
printf("  INT2CHAR GF@$$retval0 LF@i\n");
printf("  MOV GF@$$retval1 int@0\n");
printf("  JUMP CHR_LABEL_END\n");
printf("  LABEL CHR_LABEL_ERROR\n");
printf("  MOV GF@$$retval1 int@1\n");
printf("  LABEL CHR_LABEL_END\n");
printf("  POPFRAME\n");
printf("  RETURN\n");




// float2int
printf("LABEL float2int\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@f\n");
printf("  POPS LF@f\n");
printf("  DEFVAR LF@returnv\n");
printf("  FLOAT2INT LF@returnv LF@f\n");
printf("  MOVE GF@$$retval0 LF@returnv\n");
printf("  POPFRAME\n");
printf("RETURN\n");




//int2float
printf("LABEL int2float\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@i\n");
printf("  POPS LF@i\n");
printf("  DEFVAR LF@returnv\n");
printf("  INT2FLOAT LF@returnv LF@i\n");
printf("  MOVE GF@$$retval_0 LF@returnv\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");



void *safeMalloc(size_t size){
  void *ret = malloc(size);
  if(ret == NULL){
    fprintf(stderr, "Failed safeMalloc\n");
    exit(99);
  }
  return ret;
}

void *safeRealloc(void *block, size_t size){
  void *ret = realloc(block,size);
  if(ret == NULL){
    fprintf(stderr, "Failed safeRealloc\n");
    exit(99);
  }
  return ret;
}





char *string_to_ifj(char *string){
  int len = strlen(string);
  int maxLen = len + 1;
  int pos = 7;
  char *out = safeMalloc(sizeof(char) * (maxLen + 20));
  strcpy(out, "string@");

  	for(int i = 1; i < len - 1; i++){
  		if(maxLen <= pos + 4){
  			maxLen += 100;
  			out = safeRealloc(out, sizeof(char) * maxLen);
  		}

  		out[pos] = '\\';
  		if(string[i] == '\\'){
  			i++;
  			if(string[i] == '"'){
  				out[pos] = '"';
  				pos -= 3;
  			}else if(string[i] == 'n'){
  				out[pos+1] = '0';
  				out[pos+2] = '1';
  				out[pos+3] = '0';
  			}else if(string[i] == 't'){
  				out[pos+1] = '0';
  				out[pos+2] = '0';
  				out[pos+3] = '9';
  			}else if(string[i] == '\\'){
  				out[pos+1] = '0';
  				out[pos+2] = '9';
  				out[pos+3] = '2';
  			}else if(string[i] == 'x'){
  				int l = isxdigit(string[i+2])?2:1;
  				char hex[3] = {0};
  				hex[0] = string[i+1];
  				if(l > 1) hex[1] = string[i+2];
  				i += l;
  				sprintf(&out[pos+1], "%03ld", strtol(hex, NULL, 16));
  			}else{
  				out[pos+1] = '0';
  				out[pos+2] = '3';
  				out[pos+3] = '2';
  			}
  			pos += 3;
  		}else if(string[i] == ' '){
  			out[pos+1] = '0';
  			out[pos+2] = '3';
  			out[pos+3] = '2';
  			pos += 3;
  		}else if(string[i] <= '#'){
  			out[pos+1] = '0';
  			out[pos+2] = '3';
  			out[pos+3] = '5';
  			pos += 3;
  		}else{
  			out[pos] = string[i];
  		}

  		pos++;
  	}

  	out[pos] = '\0';
  	out = safeRealloc(out, sizeof(char) * (pos + 1));
  	return out;
}



char *int_to_ifj(char *rawInt){
    char *out = safeMalloc(sizeof(char)*(50));
      if(rawInt[0] == '0' && strlen(rawInt) > 1 && rawInt[1] == 'b'){
        sprintf(out, "int@%lld", strtoll(&rawInt[2], NULL, 2));
      }
      else   sprintf(out, "int@%lld", strtoll(rawInt, NULL, 0));
    return safeRealloc(out, strlen(out));
}

char *float_to_ifj(char *rawFloat){
    char *out = safeMalloc(sizeof(char)*(50));
    sprintf(out, "float@%a", strtod(rawFloat, NULL));
    return safeRealloc(out, strlen(out));
}

