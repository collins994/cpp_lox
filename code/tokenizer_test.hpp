#ifndef _H_TOKENIZER_TEST
#define _H_TOKENIZER_TEST

#define ASSERT(v) if(!(v)) {printf("FAILED ASSERTION, %s: %d\n", __FILE__, __LINE__);}

bool operator==(Token t1, Token t2) { return t1.kind == t2.kind && t1.start == t2.start && t1.end == t2.end; }

Token newToken(Kind kind, u32 start, u32 end) { Token t = {.kind = kind, .start = start, .end = end}; return t; }

void token_print(Token token, Tokenizer *tokenizer) {
	char *string_kind;
	switch(token.kind) {
		case LEFT_PAREN: string_kind = "LEFT_PAREN"; break; 
		case RIGHT_PAREN: string_kind = "RIGHT_PAREN"; break; 
		case LEFT_BRACE: string_kind = "LEFT_BRACE"; break; 
		case RIGHT_BRACE: string_kind = "RIGHT_BRACE"; break; 
		case COMMA: string_kind = "COMMA"; break; 
		case DOT: string_kind = "DOT"; break; 
		case MINUS: string_kind = "MINUS"; break; 
		case PLUS: string_kind = "PLUS"; break; 
		case SEMICOLON: string_kind = "SEMICOLON"; break; 
		case SLASH: string_kind = "SLASH"; break; 
		case STAR: string_kind = "STAR"; break; 
		case BANG: string_kind = "BANG"; break; 
		case BANG_EQUAL: string_kind = "BANG_EQUAL"; break; 
		case EQUAL: string_kind = "EQUAL"; break; 
		case EQUAL_EQUAL: string_kind = "EQUAL_EQUAL"; break; 
		case GREATER: string_kind = "GREATER"; break; 
		case GREATER_EQUAL: string_kind = "GREATER_EQUAL"; break; 
		case LESS: string_kind = "LESS"; break; 
		case LESS_EQUAL: string_kind = "LESS_EQUAL"; break; 
		case NUMBER: string_kind = "NUMBER"; break; 
		case END_OF_FILE: string_kind = "END_OF_FILE"; break;
		case INVALID: string_kind = "INVALID"; break; 
		default: string_kind = "UNKNOWN TOKEN KIND"; break;
	}

	//printf("token{kind: %s, start: %d, end: %d}\n", string_kind, token.start, token.end);
	printf("token{kind: %s, start: %d, end: %d, lexeme: %.*s}\n", string_kind, token.start, token.end, token.end - token.start, tokenizer->buffer + token.start);
}

// BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL

void tokenizer_test() {
	printf("TESTING THE TOKENIZER...\n");
	Tokenizer tokenizer = {
		.buffer = "(){},.-+;/*!=! = == > >= < <=99.8",
		.index = 0,
	};
	tokenizer.count = strlen(tokenizer.buffer);

	ASSERT(tokenizer_next_token(&tokenizer) == newToken(LEFT_PAREN, 0, 1));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(RIGHT_PAREN, 1, 2));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(LEFT_BRACE, 2, 3));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(RIGHT_BRACE, 3, 4));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(COMMA, 4, 5));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(DOT, 5, 6));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(MINUS, 6, 7));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(PLUS, 7, 8));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(SEMICOLON, 8, 9));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(SLASH, 9, 10));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(STAR, 10, 11));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(BANG_EQUAL, 11, 13));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(BANG, 13, 14));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(EQUAL, 15, 16));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(EQUAL_EQUAL, 17, 19));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(GREATER, 20, 21));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(GREATER_EQUAL, 22, 24));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(LESS, 25, 26));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(LESS_EQUAL, 27, 29));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(NUMBER, 29, 33));
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(END_OF_FILE, 33, 33));

	// for (;;){
	// 	Token next_token = tokenizer_next_token(&tokenizer);
	// 	token_print(next_token, &tokenizer);
	// 	if (next_token.kind == END_OF_FILE) break;
	// }

	printf("DONE\n");
}

#endif // _H_TOKENIZER_TEST
