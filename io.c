#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "io.h"
#include "lexer.h"

void printAST(TreeNode* head, char *prefix){
	int i = 0;
	printf("%s%s => ", prefix, head->label);
	for(i = 0; i < head->numChildren; i ++){
		printf("%s", head->children[i]->label);
		if(head->children[i]->data != 0) printf(" (%s) ", head->children[i]->data->text);
		printf(",");
	}
	printf("\n");
	char *nPrefix = strdup(prefix);
	strcat(nPrefix, "--");
	for(i = 0; i < head->numChildren; i ++){
		printAST(head->children[i], nPrefix);
	}
}

FILE* readFile(char *fileName, char *type){
	FILE* file = fopen(fileName, type);
	if(file == 0) error(ERR_LOG, -1, -1, "Unable to open file: %s", fileName);
	return file;
}

void closeFile(FILE* file){
	if(file == 0) error(ERR_SEVERE, -1, -1, "File Pointer Invalid.");
	else fclose(file);
}

void error(int type, int lineNo, int charNo, char *errorMessage, ...){
	va_list valist;
	va_start(valist, errorMessage);
	char *buffer = malloc(150);
	if(lineNo == -1) sprintf(buffer, "[Err]: %s\n", errorMessage);
	else sprintf(buffer, "[Err] (Line %d, col %d): %s\n", lineNo, charNo, errorMessage);
	vprintf(buffer, valist);
	va_end(valist);
	free(buffer);
	if(type == ERR_SEVERE){
		printf("Closing due to error being severe\n");
		exit(1);
	}
}

char* tokenToString(Token *token){
	char *buffer = malloc(99);
	char *typeStr = tokenTypeToString(token->type);
	sprintf(buffer, "{%s: %s, l %d c %d}", typeStr, token->text, token->line, token->col);
	free(typeStr);
	return buffer;
}

void printTokens(Token** tokens){
	int i = 0;
	int currLine = 0;
	while( tokens[i]->type != END){
		Token *token = tokens[i];
		while( token->line > currLine){
			printf("\n");
			currLine ++;
		}
		char* str = tokenToString(token);
		printf("%s, ", str);
		free(str);
		i++;
	}
}

char* tokenTypeToString(TokenType type){
	char *buffer = malloc(6);
	switch(type){
		default:
			sprintf(buffer, "ERR");
			break;
	}
	return buffer;
}

char fpeek(FILE *stream){
    char c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}
