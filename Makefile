.PHONY:all

TARGETS=Baghchal

all: $(TARGETS)

clean:
	@rm -f *.o *~ $(TARGETS) *.d

CC=gcc
CFLAGS=-Wall -std=c99 -g
sources=$(wildcard *.c)

# compile
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o

%.d: %.c	
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

Baghchal: gestionPions.o
	$(CC) $(CFLAGS) $^ -o $@

include $(sources:.c=.d)