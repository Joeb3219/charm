#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "io.h"

#define lookAhead(X) peek(tokens + (*current), X)
#define look() peek(tokens + (*current), 0)
#define consume() consume(tokens, current)
#define printCurrentToken() printf("[%s]: %s\n", __FUNCTION__, tokenToString(look()))
#define unexpectedToken(T) error(ERR_SEVERE, T->line, T->col, "Encountered unexepected token: %s", T->text)
#define consumeOrDie(E) {if(look()->type == E){consume();}else{unexpectedToken(look());}}

// for -> <for>
// while -> <while>
// identifier, number, ( -> expression
void stmt(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_STMT);
	addChild(head, node);
	Token *token = look();
	if(token->type == FOR) fn_for(node, tokens, current);
	if(token->type == WHILE) fn_while(node, tokens, current);
	if(token->type == IDENTIFIER || token->type == PAREN_OPEN || token->type == NUMBER) expression(node, tokens, current);
}

// identifier -> identifier = expression
void assign(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_ASSIGN);
	addChild(head, node);
	Token *token = look();
	if(token->type == IDENTIFIER){
		identifier(node, tokens, current);
		consumeOrDie(ASSIGN); // Consumes the equals sign.
		expressionOrFunc(node, tokens, current);
	}
}

// identifier (otherwise) -> expressionnonMath
// if second symbol  -, +, *, ^, / -> math
// ( -> expression
void expression(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_EXPRESSION);
	addChild(head, node);
	Token *token = look();
	Token *secondToken = lookAhead(1);
	if(token->type == IDENTIFIER){
		if(secondToken->type >= OP_ADD && secondToken->type <= OP_EXP) math(node, tokens, current);
		else expressionNonMath(node, tokens, current);
	}
	if(token->type == NUMBER){
		if(secondToken->type >= OP_ADD && secondToken->type <= OP_EXP) math(node, tokens, current);
		else expressionNonMath(node, tokens, current);
	}
	if(token->type == PAREN_OPEN){
		consumeOrDie(PAREN_OPEN); // Consume open paren
		expression(node, tokens, current);
		consumeOrDie(PAREN_CLOSE); // Consume the close paren
	}
}

// identifier = -> assign
// identifier ( -> funcExec
// identifier (otherwise) -> identifier
// number (otherwise) -> number
void expressionNonMath(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_EXPRESSION);
	addChild(head, node);
	Token *token = look();
	Token *secondToken = lookAhead(1);
	if(token->type == IDENTIFIER){
		if(secondToken->type == ASSIGN) assign(node, tokens, current);
		else if(secondToken->type == PAREN_OPEN) funcExec(node, tokens, current);
		else identifier(node, tokens, current);
	}
	if(token->type == NUMBER){
		number(node, tokens, current);
	}
}

// fn -> func
// Otherwise -> expression
void expressionOrFunc(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_EXPRESSIONORFUNC);
	addChild(head, node);
	Token *token = look();
	if(token->type == FN){
		func(node, tokens, current);
	}else{
		expression(node, tokens, current);
	}
}

// fn -> fn ( <arglist> ) { <stmtlist> }
void func(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_FUNC);
	addChild(head, node);
	if(look()->type == FN){
		consumeOrDie(FN); // Consume the fn token
		consumeOrDie(PAREN_OPEN); // Consume the ( token
		arglist(node, tokens, current);
		consumeOrDie(PAREN_CLOSE); // Consume the ) token
		consumeOrDie(CURLY_OPEN); // Consume the { token
		stmtlist(node, tokens, current);
		consumeOrDie(CURLY_CLOSE); // Consume the } token
	}
}

void identifier(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_IDENTIFIER);
	addChild(head, node);
	if(look()->type == IDENTIFIER){
		node->data = consume(); // Consume the identifier, and store the token inside the data of the node.
	}
}

void number(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_NUMBER);
	addChild(head, node);
	if(look()->type == NUMBER){
		node->data = consume(); // Consume the token, and store it into the data of the node.
	}
}

void funcExec(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_FUNCEXEC);
	addChild(head, node);
}

// identifier , -> identifier, arglist
// identifier -> identifier
// otherwise -> epsilon
void arglist(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_ARGLIST);
	addChild(head, node);
	Token *token = look(), *secondToken = lookAhead(2);
	if(token->type == IDENTIFIER){
		if(secondToken->type == COMMA){
			identifier(node, tokens, current);
			consumeOrDie(COMMA); // consume the comma token
			arglist(node, tokens, current);
		}else identifier(node, tokens, current);
	}
}

void paramlist(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_PARAMLIST);
	addChild(head, node);
}


void fn_for(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_FOR);
	addChild(head, node);
}

void fn_while(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_WHILE);
	addChild(head, node);
}

// second symbol is either +, -, /, *, or ^ -> fn_sub
void math(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_MATH);
	addChild(head, node);
	Token *secondToken = lookAhead(1);
	if(secondToken->type >= OP_ADD && secondToken->type <= OP_EXP) fn_sub(node, tokens, current);
}

void fn_sub(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_SUB);
	addChild(head, node);
	Token *secondToken = lookAhead(1);
	if(secondToken->type == OP_SUB){
		expressionNonMath(node, tokens, current);
		consumeOrDie(OP_SUB); // consume - token
		fn_add(node, tokens, current);
	}else fn_add(node, tokens, current);
}

void fn_add(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_ADD);
	addChild(head, node);
	Token *secondToken = lookAhead(1);
	if(secondToken->type == OP_ADD){
		expressionNonMath(node, tokens, current);
		consumeOrDie(OP_ADD); // consume - token
		fn_div(node, tokens, current);
	}else fn_div(node, tokens, current);
}

void fn_div(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_DIV);
	addChild(head, node);
	Token *secondToken = lookAhead(1);
	if(secondToken->type == OP_DIV){
		expressionNonMath(node, tokens, current);
		consumeOrDie(OP_DIV); // consume - token
		fn_mult(node, tokens, current);
	}else fn_mult(node, tokens, current);
}

void fn_mult(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_MULT);
	addChild(head, node);
	Token *secondToken = lookAhead(1);
	if(secondToken->type == OP_MULT){
		expressionNonMath(node, tokens, current);
		consumeOrDie(OP_MULT); // consume - token
		fn_pow(node, tokens, current);
	}else fn_pow(node, tokens, current);
}

void fn_pow(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_POW);
	addChild(head, node);
	Token *token = look(), *secondToken = lookAhead(1);
	if(secondToken->type == OP_EXP){
		expression(node, tokens, current);
		consumeOrDie(OP_EXP); // consume - token
		expression(node, tokens, current);
	} else expression(node, tokens, current);
}

// identifier, (, number, for, while -> <stmt>; <stmtlist>
// otherwise -> epsilon
void stmtlist(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_STMTLIST);
	addChild(head, node);
	Token *token = look();
	if(token->type == IDENTIFIER || token->type == NUMBER || token->type == PAREN_OPEN || token->type == FOR || token->type == WHILE){
		stmt(node, tokens, current);
		consumeOrDie(SEMICOLON); // Consume the semicolon
		stmtlist(node, tokens, current);
	}
}

// Essentially always will yield a stmtlist.
void program(TreeNode *head, Token **tokens, int *current){
	printCurrentToken();
	TreeNode *node = createNode(TN_PROGRAM);
	addChild(head, node);
	stmtlist(node, tokens, current);
	if(look()->type != END){
		error(ERR_SEVERE, look()->line, look()->col, "Encountered unexepected token: %s", look()->text);
	}
}

TreeNode *parse(Token** tokens){
	int currentToken = 0;
	TreeNode *head = createNode(TN_HEAD);
 	program(head, tokens, &currentToken);
	printAST(head, strdup("-"));
	return NULL;
}

TreeNode *createNode(TreeNodeLabel label){
	TreeNode *node = malloc(sizeof(TreeNode));

	node->label = label;
	node->numChildren = 0;
	node->data = NULL;
	node->children = NULL;

	return node;
}

void freeNode(TreeNode* node){
        int i;
        for(i = 0; i < node->numChildren; i ++){
                freeNode(node->children[i]);
        }
        if(node->children != 0) free(node->children);
        free(node);
}

void addChild(TreeNode* head, TreeNode* child){
        head->numChildren ++;
        if(head->numChildren <= 1){
                head->children = malloc(sizeof(TreeNode*));
        }else{
                head->children = realloc(head->children, head->numChildren * sizeof(TreeNode*));
        }
        head->children[head->numChildren - 1] = child;
}
