.PHONY:all

TARGETS=test_u_gestionPions test_gestionPions

all: $(TARGETS)

clean:
	@rm -f *.o *~ $(TARGETS)

CC=gcc
CFLAGS=-Wall -std=c99 -g
CLIBRARY=-lncurses
sources=$(wildcard *.c)

# compile
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o

test_u_gestionPions: test_u_gestionPions.o gestionPions.o plateau.o affichage.o save.o historique.o evenement.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBRARY)

test_gestionPions: test_gestionPions.o gestionPions.o plateau.o affichage.o save.o historique.o evenement.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBRARY)