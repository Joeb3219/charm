#ifndef PARSER_H_

#define PARSER_H_

#include "lexer.h"

struct TreeNode{
        char *label;
        struct Token* data;
        int numChildren;
        struct TreeNode** children;
};

typedef struct TreeNode TreeNode;

TreeNode *parse(Token** tokens);

#endif
