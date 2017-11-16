CC=gcc
CFLAGS=-I -Wall.
DEPS = findRects01.h
OBJ = findRects01.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

evaluate: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm  *.o evaluate
