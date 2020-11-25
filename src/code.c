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
printf("  DEFVAR LF@check\n");
printf("  READ LF@$return string\n");
printf("  TYPE LF@check LF@$return");
printf("  JUMPIFNEQ  inputs_error LF@check string@string");
printf("  MOVE GF@$$retval0 LF@$return\n");
printf("  MOVE GF@$$retval1 int@0\n");
printf("  JUMP inputs_end");
printf("  LABEL inputs_error");
printf("  MOVE GF@$$retval1 int@1\n");
printf("  LABEL inputs_end");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");


//inputi
printf("  LABEL inputi\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@$return\n");
printf("  DEFVAR LF@checki\n");
printf("  READ LF@$return int\n");
printf("  TYPE LF@checki LF@$$return\n");
printf("  JUMPIFNEQ  inputi_error LF@checki string@int\n");
printf("  MOVE GF@$$retval0 LF@$return\n");
printf("  MOVE GF@$$retval1 int@0\n");
printf("  JUMP inputi_end\n");
printf("  LABEL inputi_error\n");
printf("  MOVE GF@$$retval1 int@1\n");
printf("  LABEL inputi_end\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");

//inputf
printf("  LABEL inputf\n");
printf("  CREATEFRAME\n");
printf("  PUSHFRAME\n");
printf("  DEFVAR LF@checkf\n");
printf("  DEFVAR LF@$return\n");
printf("  READ LF@$return float\n");
printf("  TYPE LF@checkf LF@$return");
printf("  JUMPIFNEQ  inputf_error LF@checkf string@float\n");
printf("  MOVE GF@$$retval0 LF@$return\n");
printf("  MOVE GF@$$retval1 int@0\n");
printf("  JUMP inputf_end\n");
printf("  LABEL inputf_error\n");
printf("  MOVE GF@$$retval1 int@1\n");
printf("  LABEL inputf_end\n");
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
printf("  JUMPIFNEQ  print_loop LF@n int@0\n");

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
printf("  MOVE  LF@sub_string string@\n");
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
printf("  MOVE LF@tmp_string LF@sub_string");
printf("  CONCAT LF@sub_string LF@tmp_string LF@char\n");
printf("  ADD LF@i LF@i int@1\n");
printf("  SUB LF@n  LF@n int@1\n");
printf("  JUMPIFNEQ  SUB_LABEL_LOOP LF@n  int@0\n");
printf("  MOVE GF@$$retval0 LF@sub_string\n");
printf("  MOVE GF@$$retval1 int@0\n");
printf("  JUMP SUB_LABEL_END\n");


printf("  LABEL SUB_LABEL_ERROR\n");
printf("  MOVE GF@$$retval1 int@1\n");

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
printf("  DEFVAR LF@condition0\n");
printf("  POPS LF@i\n");
printf("  POPS LF@s\n");
printf("  STRLEN LF@lens LF@s\n");
printf("  LT LF@condition LF@i  LF@lens\n");
printf("  JUMPIFNEQ ORD_LABEL_ERROR LF@condition bool@true\n");
printf("  LT LF@condition0 LF@i int@0\n");
printf("  JUMPIFEQ ORD_LABEL_ERROR LF@condition0 bool@true\n");
printf("  STRI2INT GF@$$retval0 LF@s LF@i\n");
printf("  MOVE GF@$$retval1 int@0\n");
printf("  JUMP ORD_LABEL_END\n");

printf("  LABEL ORD_LABEL_ERROR\n");
printf("  MOVE GF@$$retval1 int@1\n");
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
printf("  MOVE GF@$$retval1 int@0\n");
printf("  JUMP CHR_LABEL_END\n");
printf("  LABEL CHR_LABEL_ERROR\n");
printf("  MOVE GF@$$retval1 int@1\n");
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
printf("  MOVE GF@$$retval0 LF@returnv\n");
printf("  POPFRAME\n");
printf("  RETURN\n");
printf("\n");



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
