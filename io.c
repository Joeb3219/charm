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
	char *buffer = malloc(7);
	switch(type){
		case PAREN_OPEN:
			sprintf(buffer, "(");
			break;
		case PAREN_CLOSE:
			sprintf(buffer, ")");
			break;
		case CURLY_OPEN:
			sprintf(buffer, "{");
			break;
		case CURLY_CLOSE:
			sprintf(buffer, "}");
			break;
		case IDENTIFIER:
			sprintf(buffer, "IDENT");
			break;
		case ASSIGN:
			sprintf(buffer, "=");
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
			sprintf(buffer, ";");
			break;
		case COLON:
			sprintf(buffer, ":");
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
			sprintf(buffer, "+");
			break;
		case OP_MULT:
			sprintf(buffer, "*");
			break;
		case OP_DIV:
			sprintf(buffer, "/");
			break;
		case OP_SUB:
			sprintf(buffer, "-");
			break;
		case OP_MODULO:
			sprintf(buffer, "MOD");
			break;
		case OP_EXP:
			sprintf(buffer, "^");
			break;
		case OP_AND:
			sprintf(buffer, "&&");
			break;
		case OP_OR:
			sprintf(buffer, "||");
			break;
		case OP_BIT_AND:
			sprintf(buffer, "&");
			break;
		case OP_BIT_OR:
			sprintf(buffer, "|");
			break;
		case OP_NOT:
			sprintf(buffer, "!");
			break;
		case CMP_L:
			sprintf(buffer, "<");
			break;
		case CMP_G:
			sprintf(buffer, ">");
			break;
		case CMP_LE:
			sprintf(buffer, "<=");
			break;
		case CMP_GE:
			sprintf(buffer, ">=");
			break;
		case CMP_E:
			sprintf(buffer, "==");
			break;
		case CMP_NE:
			sprintf(buffer, "!=");
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
