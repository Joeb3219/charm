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

#endif
