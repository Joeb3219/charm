#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "io.h"
#include "lexer.h"
#include "parser.h"

void printAST(TreeNode* head, int numDashes){
	int i = 0;
	for(i = 0; i < numDashes; i ++){
		printf("-");
	}
	char *label = nodeTypeToString(head->label);
	printf("%s => ", label);
	free(label);
	for(i = 0; i < head->numChildren; i ++){
		label = nodeTypeToString(head->children[i]->label);
		printf("%s", label);
		free(label);
		if(head->children[i]->data != 0) printf(" (%s) ", head->children[i]->data->text);
		printf(",");
	}
	printf("\n");
	for(i = 0; i < head->numChildren; i ++){
		printAST(head->children[i], numDashes + 1);
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

char* nodeTypeToString(TreeNodeLabel type){
	char *buffer = malloc(11);
	switch(type){
		case TN_HEAD:
			sprintf(buffer, "HEAD");
			break;
		case TN_PROGRAM:
			sprintf(buffer, "PROGRAM");
			break;
		case TN_STMTLIST:
			sprintf(buffer, "STMTLIST");
			break;
		case TN_STMT:
			sprintf(buffer, "STMT");
			break;
		case TN_ASSIGN:
			sprintf(buffer, "ASSIGN");
			break;
		case TN_EXPRESSION:
			sprintf(buffer, "EXPRESS");
			break;
		case TN_EXPRESSIONORFUNC:
			sprintf(buffer, "EXPR|FUNC");
			break;
		case TN_FUNC:
			sprintf(buffer, "FUNC");
			break;
		case TN_FUNCEXEC:
			sprintf(buffer, "FUNCEXEC");
			break;
		case TN_FOR:
			sprintf(buffer, "FOR");
			break;
		case TN_WHILE:
			sprintf(buffer, "WHILE");
			break;
		case TN_MATH:
			sprintf(buffer, "MATH");
			break;
		case TN_SUB:
			sprintf(buffer, "SUB");
			break;
		case TN_ADD:
			sprintf(buffer, "ADD");
			break;
		case TN_DIV:
			sprintf(buffer, "DIV");
			break;
		case TN_MULT:
			sprintf(buffer, "MULT");
			break;
		case TN_POW:
			sprintf(buffer, "POW");
			break;
		case TN_ARGLIST:
			sprintf(buffer, "ARGLIST");
			break;
		case TN_PARAMLIST:
			sprintf(buffer, "PARAMLIST");
			break;
		case TN_IDENTIFIER:
			sprintf(buffer, "IDENT");
			break;
		case TN_NUMBER:
			sprintf(buffer, "NUMBER");
			break;
		case TN_RET:
			sprintf(buffer, "RETURN");
			break;
		case TN_EXPRNONMATH:
			sprintf(buffer, "EXPNOMATH");
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
