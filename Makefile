CC := gcc
EXE_NAME := charm

all: clean build

build: charm.c
	$(CC) -g -o $(EXE_NAME) charm.c lexer.c compiler.c parser.c io.c

clean:
	rm -rf *.o $(EXE_NAME)
