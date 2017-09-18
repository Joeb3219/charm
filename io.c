#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "io.h"
#include "lexer.h"
#include "parser.h"

void printAST(TreeNode* head, char *prefix){
	int i = 0;
	printf("%s%d => ", prefix, head->label);
	for(i = 0; i < head->numChildren; i ++){
		printf("%d", head->children[i]->label);
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

void printTokens(FILE *file, Token** tokens){
	int i = 0;
	while( tokens[i]->type != END){
		Token *token = tokens[i];
		char* str = tokenToString(token);
		fprintf(file, "%s, ", str);
		free(str);
		i++;
	}
}

char* tokenTypeToString(TokenType type){
	char *buffer = malloc(7);
	switch(type){
		case PAREN_OPEN:
			sprintf(buffer, "PRNOPN");
			break;
		case PAREN_CLOSE:
			sprintf(buffer, "PRNCLS");
			break;
		case CURLY_OPEN:
			sprintf(buffer, "CRLOPN");
			break;
		case CURLY_CLOSE:
			sprintf(buffer, "CRLCLS");
			break;
		case IDENTIFIER:
			sprintf(buffer, "IDENT");
			break;
		case ASSIGN:
			sprintf(buffer, "ASSIGN");
			break;
		case FN:
			sprintf(buffer, "FN");
			break;
		case RET:
			sprintf(buffer, "RET");
			break;
		case NUMBER:
			sprintf(buffer, "NUM");
			break;
		case STRUCT:
			sprintf(buffer, "STRUCT");
			break;
		case SEMICOLON:
			sprintf(buffer, "SMICLN");
			break;
		case COLON:
			sprintf(buffer, "COLON");
			break;
		case IF:
			sprintf(buffer, "IF");
			break;
		case WHILE:
			sprintf(buffer, "WHILE");
			break;
		case FOR:
			sprintf(buffer, "FOR");
			break;
		case OP_ADD:
			sprintf(buffer, "ADD");
			break;
		case OP_MULT:
			sprintf(buffer, "MULT");
			break;
		case OP_DIV:
			sprintf(buffer, "DIV");
			break;
		case OP_SUB:
			sprintf(buffer, "SUB");
			break;
		case OP_MODULO:
			sprintf(buffer, "MOD");
			break;
		case OP_EXP:
			sprintf(buffer, "EXP");
			break;
		case OP_AND:
			sprintf(buffer, "AND");
			break;
		case OP_OR:
			sprintf(buffer, "OR");
			break;
		case OP_BIT_AND:
			sprintf(buffer, "BITAND");
			break;
		case OP_BIT_OR:
			sprintf(buffer, "BITOR");
			break;
		case OP_NOT:
			sprintf(buffer, "NOT");
			break;
		case CMP_L:
			sprintf(buffer, "LESSTH");
			break;
		case CMP_G:
			sprintf(buffer, "GRTRTH");
			break;
		case CMP_LE:
			sprintf(buffer, "LESSEQ");
			break;
		case CMP_GE:
			sprintf(buffer, "GRTREQ");
			break;
		case CMP_E:
			sprintf(buffer, "EQUALS");
			break;
		case CMP_NE:
			sprintf(buffer, "NTEQLS");
			break;
		case COMMA:
			sprintf(buffer, "COMMA");
			break;
		case END:
			sprintf(buffer, "END");
			break;
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
