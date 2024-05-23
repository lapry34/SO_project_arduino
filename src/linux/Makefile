CC=g++
CCOPTS=-std=c++17 -O3 -Wall 
BINS=serial_linux

.phony: clean all

all: $(BINS)

serial_linux:	serial_linux.cpp main.cpp
	$(CC) -$(CCOPTS) -o $@ $^  

clean:
	rm -rf *~ $(BINS) *.pgm

