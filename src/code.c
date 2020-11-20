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



          // -- TODO -- //
  //add  all inbuit function... //
}
char *stringToInterpret(char *rawString){
	//int rawLen = strlen(rawString);



// TODO //
	return rawString;
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
