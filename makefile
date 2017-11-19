CC=gcc
CFLAGS=-I.
DEPS = findRects01.h
OBJ = findRects01.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -Wall -g -o $@ $< $(CFLAGS)

evaluate: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm  *.o evaluate
