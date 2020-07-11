CC     = gcc
CFLAGS = -std=c99 -pedantic -g -Werror -Wall 
BUILD  = dynarray_generic.o

.PHONY: all clean 

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD)
	/bin/rm -f *.o

dynarray_generic.o: dynarray_generic.h
