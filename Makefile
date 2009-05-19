CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O1 -Iinclude

all: myvm.o vmfile.o
	$(CC) -o myvm $+


clean: 
	rm -f *.o
	rm -f myvm
