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
typedef struct SyntaxStack{
    tType *a;   // Pole neterminálů/terminálů
    int size;
    int top;    // Index prvního volného místa
	int last;   // Index naposledy vloženého prvku
}synt_stack;
