.PHONY:all

TARGETS=test_u_gestionPions test_gestionPions test_u_rechercheVainqueur test_rechercheVainqueur

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

test_u_rechercheVainqueur: test_u_rechercheVainqueur.o gestionPions.o plateau.o affichage.o save.o historique.o evenement.o rechercheVainqueur.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBRARY)

test_rechercheVainqueur: test_rechercheVainqueur.o gestionPions.o plateau.o affichage.o save.o historique.o evenement.o rechercheVainqueur.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBRARY)