CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O1 -Iinclude

all: myvm
	@echo "All done"

myvm: vmstate.o vminst.o vmfile.o myvm.o
	$(CC) -o myvm $+


clean: 
	rm -f *.o
	rm -f myvm
