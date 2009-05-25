CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O1 -Iinclude
LDFLAGS=-L./ -lmyvm
AR=ar
ARFLAGS=csr

all: myvm myasm
	@echo "All done"

myvm: myvm.o libmyvm.a
	$(CC) -o myvm myvm.o $(LDFLAGS)

myasm: myasm.o libmyvm.a
	$(CC) -o myasm myasm.o $(LDFLAGS)


libmyvm.a: vm.o ops.o vmstate.o vminst.o vmfile.o
	$(AR) $(ARFLAGS) $@ $+

clean: 
	rm -f *.o *.a
	rm -f myvm
	rm -f myasm
