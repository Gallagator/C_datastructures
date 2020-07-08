CC     = gcc
CFLAGS = -std=c99 -pedantic -g -Werror -Wall -I./../../../testing/
LDLIBS = -L./../../../testing/ -ltestlib
BUILD  = dynarrayChar.o

.PHONY: all clean test_util test

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD)
	/bin/rm -f dynarrayChartests 
	/bin/rm -f *.o
	cd ./../../../testing; make clean

test: test_util dynarrayChartests
	./dynarrayChartests

test-full: test_util dynarrayChartests
	valgrind ./dynarrayChartests

dynarrayChartests: $(BUILD) dynarrayChartests.o 

dynarrayChartests.o: dynarrayChartests.c

test_util:
	cd ./../../../testing; make

dynarray.o: dynarrayChar.h
