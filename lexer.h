#ifndef LEXER_H

#define LEXER_H

enum TokenType{

	PAREN_OPEN, PAREN_CLOSE, CURLY_OPEN, CURLY_CLOSE, COMMA,

	IDENTIFIER, ASSIGN, FN, RET, NUMBER, STRUCT, SEMICOLON, COLON, IF, WHILE, FOR,

	OP_ADD, OP_MULT, OP_SUB, OP_DIV, OP_MODULO, OP_EXP, OP_AND, OP_OR, OP_BIT_AND, OP_BIT_OR, OP_NOT,

	CMP_L, CMP_G, CMP_LE, CMP_GE, CMP_E, CMP_NE,

	END

};

struct Token{
	char *text;
	int line;
	int col;
	enum TokenType type;
};

typedef enum TokenType TokenType;
typedef struct Token Token;

Token** getTokens(FILE* file);

#endif
