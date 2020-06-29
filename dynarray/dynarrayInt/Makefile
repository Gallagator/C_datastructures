CC     = gcc
CFLAGS = -std=c99 -pedantic -g -Werror -Wall 
BUILD  = dynarrayInt.o

.PHONY: all clean 

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD)
	/bin/rm -f *.o

dynarrayInt.o: dynarrayInt.h
