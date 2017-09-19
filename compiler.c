#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"
#include "parser.h"
#include "lexer.h"
#include "io.h"
#include "hashmap.h"

void compile(FILE* file, TreeNode* head){
	Hashmap* lookupTable = generateHashmap();

	fprintf(file, "#include <stdlib.h>\n");

	fprintf(file, "int main(){\n");
	fprintf(file, "return 0;\n");
	fprintf(file, "}\n");

	destroyHashmap(lookupTable);
}
