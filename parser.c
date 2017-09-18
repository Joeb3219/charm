#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

void program(TreeNode *head, Token **tokens, int *current){
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
