CC=gcc
CCOPTS=-std=gnu99 -Ofast -Wall -Wextra -I. 
BINS=serial_linux

.PHONY: clean all run default

default: clean all run clean

all: $(BINS)

serial_linux: serial_linux.c main.c utils.c
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *~ $(BINS) *.pgm

run:
	./serial_linux /dev/ttyUSB0 19200 data.gnuplot
