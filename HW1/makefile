CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: 18050111056.o hellofunc.o 
	$(CC) -o hellomake 18050111056.o hellofunc.o 
