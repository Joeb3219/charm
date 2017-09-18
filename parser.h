#ifndef PARSER_H_

#define PARSER_H_

#include "lexer.h"

enum TreeNodeLabel{
	TN_HEAD, TN_PROGRAM, TN_STMTLIST, TN_STMT, TN_ASSIGN, TN_EXPRESSION,
	TN_EXPRESSIONORFUNC, TN_FUNC, TN_FUNCEXEC, TN_FOR, TN_WHILE, TN_MATH, TN_SUB,
	TN_ADD, TN_DIV, TN_MULT, TN_POW, TN_ARGLIST, TN_PARAMLIST
};

struct TreeNode{
        enum TreeNodeLabel label;
        struct Token* data;
        int numChildren;
        struct TreeNode** children;
};

typedef struct TreeNode TreeNode;
typedef enum TreeNodeLabel TreeNodeLabel;

TreeNode *parse(Token** tokens);
TreeNode *createNode(TreeNodeLabel label);
void addChild(TreeNode* head, TreeNode* child);

void program(TreeNode *head, Token **tokens, int *current);
void stmtlist(TreeNode *head, Token **tokens, int *current);
void stmt(TreeNode *head, Token **tokens, int *current);
void assign(TreeNode *head, Token **tokens, int *current);
void expressionOrFunc(TreeNode *head, Token **tokens, int *current);
void expression(TreeNode *head, Token **tokens, int *current);
void func(TreeNode *head, Token **tokens, int *current);
void funcExec(TreeNode *head, Token **tokens, int *current);
void arglist(TreeNode *head, Token **tokens, int *current);
void paramlist(TreeNode *head, Token **tokens, int *current);
void fn_for(TreeNode *head, Token **tokens, int *current);
void fn_while(TreeNode *head, Token **tokens, int *current);
void math(TreeNode *head, Token **tokens, int *current);
void fn_sub(TreeNode *head, Token **tokens, int *current);
void fn_add(TreeNode *head, Token **tokens, int *current);
void fn_div(TreeNode *head, Token **tokens, int *current);
void fn_mult(TreeNode *head, Token **tokens, int *current);
void fn_pow(TreeNode *head, Token **tokens, int *current);

#endif
