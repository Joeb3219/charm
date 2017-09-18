#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "io.h"

#define peek() peek(tokens + (*current), 0)
#define consume() consume(tokens, current)
#define printCurrentToken() printf("%s\n", tokenToString(peek()))

// for -> <for>
// while -> <while>
// identifier, number, ( -> expression
void stmt(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_STMT);
	addChild(head, node);
	Token *token = peek();
	printCurrentToken();
	if(token->type == FOR) fn_for(node, tokens, current);
	if(token->type == WHILE) fn_while(node, tokens, current);
	if(token->type == IDENTIFIER || token->type == PAREN_OPEN || token->type == NUMBER) expression(node, tokens, current);
}

void assign(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_ASSIGN);
	addChild(head, node);
}

void expression(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_EXPRESSION);
	addChild(head, node);
}

void func(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_FUNC);
	addChild(head, node);
}

void funcExec(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_FUNCEXEC);
	addChild(head, node);
}

void arglist(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_ARGLIST);
	addChild(head, node);
}

void paramlist(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_PARAMLIST);
	addChild(head, node);
}

void fn_for(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_FOR);
	addChild(head, node);
}

void fn_while(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_WHILE);
	addChild(head, node);
}

void math(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_MATH);
	addChild(head, node);
}

void fn_sub(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_SUB);
	addChild(head, node);
}

void fn_add(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_ADD);
	addChild(head, node);
}

void fn_div(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_DIV);
	addChild(head, node);
}

void fn_mult(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_MULT);
	addChild(head, node);
}

void fn_pow(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_POW);
	addChild(head, node);
}

// identifier, (, number, for, while -> <stmt>; <stmtlist>
// otherwise -> epsilon
void stmtlist(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_STMTLIST);
	addChild(head, node);
	Token *token = peek();
	printCurrentToken();
	if(token->type == IDENTIFIER || token->type == NUMBER || token->type == PAREN_OPEN || token->type == FOR || token->type == WHILE){
		stmt(node, tokens, current);
		consume();
		stmtlist(node, tokens, current);
	}
}

void program(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_PROGRAM);
	addChild(head, node);
	stmtlist(node, tokens, current);
}

TreeNode *parse(Token** tokens){
	int currentToken = 0;
	TreeNode *head = createNode(TN_HEAD);
 	program(head, tokens, &currentToken);
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
