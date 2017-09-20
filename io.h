#ifndef _IO_H_
	#define _IO_H_

	#include "lexer.h"
	#include "parser.h"

	#define ERR_LOG 0
	#define ERR_SEVERE 1

	FILE* readFile(char *fileName, char *type);
	void closeFile(FILE* file);
	void error(int type, int lineNo, int charNo, char* errorMessage, ...);

	char* tokenTypeToString(TokenType type);
	char* tokenToString(Token *token);
	void printTokens(FILE *file, Token** tokens);
	char* nodeTypeToString(TreeNodeLabel type);

	char fpeek(FILE* stream);

	void printAST(TreeNode* head, int numDashes);

	char* appendString(char* a, char* b);

#endif
