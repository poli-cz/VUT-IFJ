/**
 * @file symtable.c
 *
 * Hlavičkový soubor pro parser
 *
 * IFJ Projekt 2020, Tým 2
 *
 * @author <xpolis04> Jan Polišenský
 */


#define STACK_CHUNK_SIZE 1000                      // Velikost alokační jednotky zásobníku

/**
 * Pomocný zásobník k rekurzivnímu sestupu, probíhá na něm rozklad neterminálů na terminály
 */
typedef struct teminal{
  int test;

}T_term;

// structure of syntax_stact
typedef struct SyntaxStack{
    T_term t;   // Pole neterminálů/terminálů
    int size;
    int top;    // Index prvního volného místa
	int last;   // Index naposledy vloženého prvku
}synt_stack;

// function prototypes

int       parser          ();
int       parser_debug    ();
void      stack_init      (synt_stack *stack, int err_code);
