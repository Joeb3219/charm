CC := gcc
EXE_NAME := charm

all: clean build

build: charm.c
	$(CC) -g -o $(EXE_NAME) *.c

clean:
	rm -rf *.o $(EXE_NAME)
