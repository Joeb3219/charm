#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "io.h"
#include "parser.h"
#include "compiler.h"

// Searches through the input arguments to find the executable name
// If specified via the format -O <name>, will return <name>
// If there is no -O, or -O is the last option in the call (ie: nothing follows -O), will return "a.out".
char* getExecutableName(int argc, char **argv){
	int i = 0;
	// We only go to argc - 1 since if -O is the very last input, there is no name following it.
	// Thus, it's pointless to check.
	for(i = 0; i < argc - 1; i ++){
		if(strcmp(argv[i], "-O") == 0) return strdup(argv[i + 1]);
	}
	return strdup("a.out");
}

int main(int argc, char **argv){

	// If there is no arguments passed, we die on this hill.
	if(argc < 2){
		error(ERR_SEVERE, -1, -1, "Invalid parameter count. Usage: %s <filename>, or %s -h for more commands", argv[0], argv[0]);
		return 1;
	}

	// If the user asked for help, we can help them.
	// Requires that the flag is first.
	// TODO: Allow flag to be in any position 9/19/17
	if(strcmp(argv[1], "-h") == 0){
		printf("Usage: %s <filename> [flags]\n", argv[0]);
		printf("Available flags:\n");
		printf("-O <executableName>");
		return 0;
	}

	// This is the input file of source code.
	FILE* file = readFile(argv[1], "r");

	if(file == 0) return 1;

	// Respectively, these are the tokens output file, and the c output file.
	// The tokens output file is fairly useless to the user, but may be useful in debugging the tokenizer.
	// The cOut file is the C code generated by the compiler, which is later used to generate an actual executable.
	FILE* tokenOut = readFile("token.out", "w");
	FILE* cOut = readFile("cout.c", "w");

	// Now we actually tokenize, and then build the program.
	Token **tokens = getTokens(file);

	// As we have the tokenized file, we no longer need the file anymore.
	closeFile(file);

	// Prints the tokens to the output file, for debugging as specified above.
	// TODO: Flag to control whether or not tokens/AST is printed to screen/file/at all 9/19/17
	printTokens(tokenOut, tokens);
	closeFile(tokenOut);

	// Now begins parsing. This is a fairly expensive operation, and builds an AST.
	TreeNode* head = parse(tokens);

	// Compilation converts the AST into a c program, which is printed into the file cOut.
	// TODO: Allow printing the resultant C code to screen/file/both 9/19/17.
	compile(cOut, head);
	closeFile(cOut);

	// Now that we've built a C program as output, we can go ahead and use GCC to build the exe
	// TODO: allow other compilers than GCC 9/19/17
	char *executableName = getExecutableName(argc, argv);
	printf("Creating executable %s\n", executableName);
	char *command = malloc(255); // TODO: ensure this is actually safe to memory overflows 9/19/17
	sprintf(command, "gcc -o %s cout.c", executableName);
	system(command);
	free(command);
	free(executableName);

	// Free the tokens and AST to avoid memory leaks.
	freeTokens(tokens);
	freeNode(head);

	printf("\n");

	return 0;
}
