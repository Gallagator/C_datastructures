CC = gcc
CFLAGS = -Wall -pedantic -g
LIB = libtestlib.a
BUILD = test_utils.o $(LIB) 
LIBOBJS = test_utils.o

all: $(LIB)

clean:
	/bin/rm -f *.a *.o core

$(LIB):  $(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

test_utils.o: test_utils.h
