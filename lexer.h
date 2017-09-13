#ifndef LEXER_H

#define LEXER_H

enum TokenType{

	PAREN_OPEN, PAREN_CLOSE, CURLY_OPEN, CURLY_CLOSE,

	LET, VARIABLE, ASSIGN, INT,

	OP_ADD, OP_MULT, OP_SUB, OP_DIV, OP_MODULO,

	CMP_L, CMP_G, CMP_LE, CMP_GE, CMP_E, NOT,

	END

};

struct Token{
	char *text;
	int line;
	int col;
	enum TokenType type;
};

struct TreeNode{
        char *label;
        struct Token* data;
        int numChildren;
        struct TreeNode** children;
};

typedef enum TokenType TokenType;
typedef struct Token Token;;
typedef struct TreeNode TreeNode;

#endif
