#ifndef COMPILER_H_
#define COMPILER_H_

	#include "parser.h"
	#include "io.h"
	#include "lexer.h"

	void compile(FILE *file, TreeNode *head);

#endif
