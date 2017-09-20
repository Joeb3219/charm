#ifndef COMPILER_H_
#define COMPILER_H_

	#include "parser.h"
	#include "io.h"
	#include "lexer.h"
	#include "hashmap.h"

	enum ValueType{
		FUNCTION, INT, VOID
	};

	struct Function{
		TreeNode *start;
		TreeNode *stmtlist;
		TreeNode *arguments;
		enum ValueType type;
	};

	struct Variable{
		struct Function *container;
		TreeNode *start;
		TreeNode *name;
		TreeNode *value;
		enum ValueType type;
	};

	typedef struct Function Function;
	typedef struct Variable Variable;
	typedef enum ValueType ValueType;

	void compile(FILE *file, TreeNode *head);
	Function *createFunction(TreeNode* start, TreeNode* stmtlist, TreeNode* args);
	Variable *createVariable(TreeNode *start, TreeNode *name, TreeNode *value);
	void findFunctionType(Function *function);
	void findVariableType(Variable *variable);

	char* valueTypeToString(ValueType type);

#endif
