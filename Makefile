lex: lex.c ; gcc -std=c99 -g -Wall -pedantic -o lex lex.c

.PHONY: clean
clean: ; rm -f lex
