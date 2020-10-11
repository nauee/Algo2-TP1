CFLAGS=-g -std=c99 -Wall -Werror -Wconversion

evento_pesca: evento_pesca.c main.c
	gcc evento_pesca.c main.c $(CFLAGS) -o evento_pesca

ejecutar: evento_pesca
	clear
	./evento_pesca

debug: evento_pesca
	gdb ./evento_pesca