CC     = gcc
CFLAGS = -std=c99 -pedantic -g -Werror -Wall 
BUILD  = dynarrayGen.o

.PHONY: all clean 

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD)
	/bin/rm -f *.o

dynarrayGen.o: dynarrayGen.h
