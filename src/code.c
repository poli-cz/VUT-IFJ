#include "codegen.h"


void main_code(){
  // base code generation
  printf(".IFJcode20\n\
  DEFVAR GF@input_prompt\n\
  CREATEFRAME\n\
  PUSHFRAME\n\
  JUMP main$\n\
  \n\
LABEL inputs$\n\
  PUSHFRAME\n\
  DEFVAR LF@$return\n\
  READ LF@$return string\n\
  POPFRAME\n\
  RETURN\n\
LABEL print$\n\
  DEFVAR LF@out\n\
  POPS LF@out \n\
  WRITE LF@out\n\
  POPFRAME\n\
	RETURN\n");



          // -- TODO -- //
  //add  all inbuit function... //
}

/*

char *string_to_ifj(char *string){

//----TODO ----//

}

char *int_to_ifj(int i){

  //----TODO ----//

}

char *float_to_ifj(char *float){

  //----TODO ----//

}
*/

// atd, prost víc funkcí na převádění normalních data typů
// na ty fakin IFJ20 datové typy
