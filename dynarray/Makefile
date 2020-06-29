CC     = gcc
CFLAGS = -std=c99 -pedantic -g -Werror -Wall -I./../testing/
LDLIBS = -L./../testing/ -ltestlib
BUILD  = dynarray.o

.PHONY: all clean test_util test

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD)
	/bin/rm -f dynarraytests 
	/bin/rm -f *.o
	cd ./../testing; make clean

test: test_util dynarraytests
	./dynarraytests

dynarraytests: $(BUILD) dynarraytests.o 

dynarraytests.o: dynarraytests.c

test_util:
	cd ./../testing; make

dynarray.o: dynarray.h
