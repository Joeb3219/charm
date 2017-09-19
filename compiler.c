#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"
#include "parser.h"
#include "lexer.h"
#include "io.h"

// We use a FNV-1a hash, as described https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
unsigned long long hash(char* key){
	unsigned long long value = (unsigned long long) 14695981039346656037L;
	unsigned long long fnvPrime = 1099511628211L;
	int i = 0, length = strlen(key);
	for(i = 0; i < length; i ++){
		value = value * fnvPrime;
		value = value ^ key[i];
	}
	return value;
}

void compile(FILE* file, TreeNode* head){
	fprintf(file, "#include <stdlib.h>\n");


	fprintf(file, "int main(){\n");
	fprintf(file, "return 0;\n");
	fprintf(file, "}\n");
}
