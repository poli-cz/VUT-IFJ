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
  \n\
LABEL inputs$\n\
  PUSHFRAME\n\
  DEFVAR LF@$return\n\
  READ LF@$return string\n\
  MOVE GF@$$retval0 LF@$return\n\
  POPFRAME\n\
	RETURN\n\
  \n\
LABEL inputi$\n\
  PUSHFRAME\n\
  DEFVAR LF@$return\n\
  READ LF@$return int\n\
  MOVE GF@$$retval0 LF@$return\n\
  POPFRAME\n\
  RETURN\n\
    \n\
LABEL inputf$\n\
  PUSHFRAME\n\
  DEFVAR LF@$return\n\
  READ LF@$return float\n\
  MOVE GF@$$retval0 LF@$return\n\
  POPFRAME\n\
	RETURN\n\n");



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

