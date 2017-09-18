#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

#define SUCCESS 1
#define FAILURE 0

int program(TreeNode *head, Token **tokens, int *current){
	TreeNode *node = createNode(TN_PROGRAM);
	addChild(head, node);
	return SUCCESS;
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
