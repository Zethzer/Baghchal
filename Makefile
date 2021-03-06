.PHONY:all

TARGETS=Baghchal

all: $(TARGETS)

clean:
	@rm -f *.o *~ $(TARGETS) *.d

CC=gcc
CFLAGS=-Wall -std=c99 -g
CLIBRARY=-lncurses
sources=$(wildcard *.c)

# compile
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o

%.d: %.c	
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

Baghchal: main.o jouer.o plateau.o evenement.o gestionPions.o historique.o affichage.o save.o rechercheVainqueur.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBRARY)

include $(sources:.c=.d)