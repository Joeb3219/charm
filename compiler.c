#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"
#include "parser.h"
#include "lexer.h"
#include "io.h"
#include "hashmap.h"

// Goes through entire head, and finds all of the functions and generates their code.
void compileFunctions(FILE* file, TreeNode* head, Hashmap* table){
	if(head->label == FN_FUNC){

	}
}

void compile(FILE* file, TreeNode* head){
	Hashmap* lookupTable = generateHashmap();

	fprintf(file, "#include <stdlib.h>\n");

	fprintf(file, "int main(){\n");
	fprintf(file, "return 0;\n");
	fprintf(file, "}\n");

	destroyHashmap(lookupTable);
}
