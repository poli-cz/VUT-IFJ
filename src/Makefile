


PROJ=proj
# sem pridejte .c soubory
FILES=main.c scanner.c dynamic_string.c symtable.c parsing_preprocesor.c parser.c
									# az se budou delat legit testy tohle oddelejte
CFLAGS=-std=gnu99 #-Wall -Wextra -Werror -pedantic -pthread
CC=gcc
RM=rm -f

all : $(PROJ)

$(PROJ) : $(FILES)
		$(CC) $(CFLAGS) -o $(PROJ) $(FILES) -lm


clean :
	$(RM) *.o $(PROJ)
