CC = gcc
CFLAGS = -g -Wall -D DEBUG
DEPS = brainfuck.h
OBJ = brainfuck.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

brainfuck: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJ)