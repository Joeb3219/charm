#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "lexer.h"

Token* peek(Token** tokens, int distance){
	int i;
	for(i = 0; i < distance; i ++){
		if(tokens[i]->type == END) return NULL;
	}
	return tokens[distance];
}

// Returns 1 if the sequence is a number, or 0 otherwise.
int isNumber(char *sequence){
	int i;
	char c;
	for(i = 0; i < strlen(sequence); i ++){
		if(sequence[i] > '9' || sequence[i] < '0') return 0;
	}
	return 1;
}

// Returns 1 if the sequence is an identifier, or 0 otherwise.
int isIdentifier(char *sequence){
	int i;
	char c;
	for(i = 0; i < strlen(sequence); i ++){
		c = sequence[i];
		if(i == 0 && !( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) return 0;
		else if(!( (c >= '0' && c <= '9') || (c == '_') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) return 0;
	}
	return 1;
}

char* getCharactersUntilDelimiter(FILE* file){
	char *buffer = malloc(32);
	char c;
	int count = 0;

	while((c = fgetc(file)) != EOF){
		if(c == '\n'|| c == ' ' || c == '\0' || c == '\t' || c == '\r') break;
		buffer[count] = c;
		count ++;
	}

	buffer[count] = '\0';

	// If c is a delimiter, we will end up under counting how many chars we've actually read.
	// If we hit EOF, we don't actually count that character via count.
	// In either case, we've read 1 more character than count equals.
	// So we seek back count - 1 to get back to where we started at the beginning of the function call.
	fseek(file, -count - 1, SEEK_CUR);

	return buffer;
}

void identifyType(Token* token, FILE* file){
	int initialBlockLength = 0;
	TokenType type = -1;

	token->text = NULL;

	char current = fpeek(file);

	if(current == ' ' || current == '\0' || current == '\t' || current == '\r' || current == '\n'){
		token->type = -1;
		type = -2;
		token->text = strdup("");
	 // Error, we are trying to find a token from an invalid start.
	}

	char *block = getCharactersUntilDelimiter(file);
	initialBlockLength = strlen(block);

	if(strlen(block) == 0){
		error(ERR_SEVERE, -1, -1, "GG");
	}

	// Strategy: while length is greater than largest non-id/num length, check if id or number,
	// and then if not, append an \0 to the end of the string
	// eventually, the length will either be the right size (<= 6), or we will have found an identifier/number.
	while(type == -1 && strlen(block) > 6){
		if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	if(type == -1 && strlen(block) == 6){
		if(strcmp(block, "struct") == 0) type = STRUCT;
		else if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	if(type == -1 && strlen(block) == 5){
		if(strcmp(block, "while") == 0) type = WHILE;
		else if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	if(type == -1 && strlen(block) == 4){
		if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	if(type == -1 && strlen(block) == 3){
		if(strcmp(block, "for") == 0) type = FOR;
		else if(strcmp(block, "ret") == 0) type = RET;
		else if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	if(type == -1 && strlen(block) == 2){
		if(strcmp(block, "fn") == 0) type = FN;
		else if(strcmp(block, "if") == 0) type = IF;
		else if(strcmp(block, "<=") == 0) type = CMP_LE;
		else if(strcmp(block, ">=") == 0) type = CMP_GE;
		else if(strcmp(block, "==") == 0) type = CMP_E;
		else if(strcmp(block, "!=") == 0) type = CMP_NE;
		else if(strcmp(block, "&&") == 0) type = OP_AND;
		else if(strcmp(block, "||") == 0) type = OP_OR;
		else if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	if(type == -1 && strlen(block) == 1){
		if(strcmp(block, "(") == 0) type = PAREN_OPEN;
		else if(strcmp(block, ")") == 0) type = PAREN_CLOSE;
		else if(strcmp(block, "{") == 0) type = CURLY_OPEN;
		else if(strcmp(block, "}") == 0) type = CURLY_CLOSE;
		else if(strcmp(block, ";") == 0) type = SEMICOLON;
		else if(strcmp(block, "<") == 0) type = CMP_L;
		else if(strcmp(block, ">") == 0) type = CMP_G;
		else if(strcmp(block, "=") == 0) type = ASSIGN;
		else if(strcmp(block, "+") == 0) type = OP_ADD;
		else if(strcmp(block, "-") == 0) type = OP_SUB;
		else if(strcmp(block, "*") == 0) type = OP_MULT;
		else if(strcmp(block, "/") == 0) type = OP_DIV;
		else if(strcmp(block, "%") == 0) type = OP_MODULO;
		else if(strcmp(block, "^") == 0) type = OP_EXP;
		else if(strcmp(block, "&") == 0) type = OP_BIT_AND;
		else if(strcmp(block, "|") == 0) type = OP_BIT_OR;
		else if(strcmp(block, ":") == 0) type = COLON;
		else if(strcmp(block, "!") == 0) type = OP_NOT;
		else if(strcmp(block, ",") == 0) type = COMMA;
		else if(isIdentifier(block) == 1) type = IDENTIFIER;
		else if(isNumber(block) == 1) type = NUMBER;
		else block[strlen(block) - 1] = '\0';
	}

	// Now that we've read all of the characters, we move forward as appropriate.
	fseek(file, strlen(block), SEEK_CUR);

	if(type == -1){
		type = END;
		error(ERR_SEVERE, -1, -1, "Unknown symbol: %s", block);
	}

	if(token->text == 0){
		token->type = type;
		token->text = block;
	}
}

// Returns all of the tokens in a file with details in the Token struct.
Token** getTokens(FILE* file){
	Token** tokens = NULL;
	int numTokens = 0;
	int i, lineNo = 0, colNo = -1;

	char c;
	while( (c = fpeek(file)) != EOF){
		// If we encounter a space character, we consume the character and advance to the next character.
		if(c == ' ' || c == '\t' || c == '\r'){
			colNo ++;
			fgetc(file);	// Consumes the character to advance the file pointer.
			continue;
		// If we encounter a new line symbol, we advance to the next line and consume the character.
		}else if(c == '\n'){
			lineNo ++;
			colNo = -1;	// Go back to the start column.
			fgetc(file);	// Consume the character to advance the file pointer.
			continue;
		}

		colNo ++;

		// If we are at this point, we have actually got a token on our hands!
		// Let's allocate space for the Token to push into our array.
		Token* token = malloc(sizeof(Token));
		token->line = lineNo;
		token->col = colNo;

		// Get details of what the type of token we're looking at, to be stored right in our struct.
		identifyType(token, file);

		// We now can allocate space in our array of tokens for this token, and then pop it onto the end.
		if(numTokens == 0) tokens = malloc(sizeof(Token) * 1);
		else tokens = realloc(tokens, (numTokens + 1) * sizeof(Token));
		tokens[numTokens] = token;
		numTokens ++;

	}

	// Now we create an "END" token, which is the endpoint of our program.
	tokens = realloc(tokens, (numTokens + 1) * sizeof(Token*));
	tokens[numTokens] = malloc(sizeof(Token));
        tokens[numTokens]->type = END;
        tokens[numTokens]->line = lineNo;
	tokens[numTokens]->col = colNo;

	return tokens;
}
