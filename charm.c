#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "io.h"

int main(int argc, char **argv){

	if(argc != 2){
		error(ERR_SEVERE, -1, -1, "Invalid parameter count. Usage: %s <filename>", argv[0]);
		return 1;
	}

	FILE* file = readFile(argv[1], "r");

	if(file == 0) return 1;

	closeFile(file);

	return 0;
}
