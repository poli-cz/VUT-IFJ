


PROJ=proj
# sem pridejte .c soubory
FILES=main.c scanner.c dynamic_string.c symtable.c parsing_preprocesor.c parser.c basic.c PSA.c psa_prerun.c codegen.c code.c
								
CFLAGS=-std=gnu99 -Wall -pedantic -Werror # -Wextra
CC=gcc
RM=rm -f

all : $(PROJ)

$(PROJ) : $(FILES)
		$(CC) $(CFLAGS) -o $(PROJ) $(FILES) -lm


clean :
	$(RM) *.o $(PROJ)
