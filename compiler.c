#include <stdlib.h>
#include <stdio.h>
#include "compiler.h"
#include "parser.h"
#include "lexer.h"
#include "io.h"

void compile(FILE* file, TreeNode* head){
	fprintf(file, "#include <stdlib.h>\n");


	fprintf(file, "int main(){\n");
	fprintf(file, "return 0;\n");
	fprintf(file, "}\n");
}
