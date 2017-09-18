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

int program(TreeNode *head, Token **tokens, int *current);
int stmtlist(TreeNode *head, Token **tokens, int *current);
int stmt(TreeNode *head, Token **tokens, int *current);
int assign(TreeNode *head, Token **tokens, int *current);
int expressionOrFunc(TreeNode *head, Token **tokens, int *current);
int expression(TreeNode *head, Token **tokens, int *current);
int func(TreeNode *head, Token **tokens, int *current);
int funcExec(TreeNode *head, Token **tokens, int *current);
int arglist(TreeNode *head, Token **tokens, int *current);
int paramlist(TreeNode *head, Token **tokens, int *current);
int fn_for(TreeNode *head, Token **tokens, int *current);
int fn_while(TreeNode *head, Token **tokens, int *current);
int math(TreeNode *head, Token **tokens, int *current);
int fn_sub(TreeNode *head, Token **tokens, int *current);
int fn_add(TreeNode *head, Token **tokens, int *current);
int fn_div(TreeNode *head, Token **tokens, int *current);
int fn_mult(TreeNode *head, Token **tokens, int *current);
int fn_pow(TreeNode *head, Token **tokens, int *current);

#endif
