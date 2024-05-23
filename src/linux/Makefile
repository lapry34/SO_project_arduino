CC=gcc
CCOPTS=-std=gnu99 -O3 -Wall 
BINS=serial_linux

.phony: clean all

all: $(BINS)

serial_linux:	serial_linux.c main.c
	$(CC) -$(CCOPTS) -o $@ $^  

clean:
	rm -rf *~ $(BINS) *.pgm

