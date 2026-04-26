#ifndef _H_TOKENIZER_TEST
#define _H_TOKENIZER_TEST

#define ASSERT(v) if(!(v)) {printf("FAILED ASSERTION, FILE: %s, LINE: %d\n", __FILE__, __LINE__);}

bool operator==(Token t1, Token t2) { return t1.kind == t2.kind && t1.start == t2.start && t1.end == t2.end; }

Token newToken(Kind kind, u32 start, u32 end) { Token t = {.kind = kind, .start = start, .end = end}; return t; }

void token_print(Token token) {
	printf("token{kind: %d, start: %d, end: %d}\n", token.kind, token.start, token.end);
}

void tokenizer_test() {
	printf("RUNNING TESTS:\n");
	Tokenizer tokenizer = {
		.buffer = "(){},.-+;/*!=",
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
	ASSERT(tokenizer_next_token(&tokenizer) == newToken(END_OF_FILE, 13, 13));

	printf("DONE\n");
}

#endif // _H_TOKENIZER_TEST
