#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "io.h"
#include "parser.h"

int main(int argc, char **argv){


	if(argc != 2){
		error(ERR_SEVERE, -1, -1, "Invalid parameter count. Usage: %s <filename>", argv[0]);
		return 1;
	}

	FILE* file = readFile(argv[1], "r");

	if(file == 0) return 1;

	FILE* tokenOut = readFile("token.out", "w");

	Token **tokens = getTokens(file);

	// As we have the tokenized file, we no longer need the file anymore.
	closeFile(file);

	printTokens(tokenOut, tokens);

	closeFile(tokenOut);

	TreeNode* head = parse(tokens);

	freeTokens(tokens);
	freeNode(head);

	printf("\n");

	return 0;
}
