#ifndef _H_TOKENIZER_TEST
#define _H_TOKENIZER_TEST

#define ASSERT(v) if(!(v)) {printf("FAILED ASSERTION, FILE: %s, LINE: %d\n", __FILE__, __LINE__);}

bool operator==(Token t1, Token t2) { return t1.kind == t2.kind && t1.start == t2.start && t1.end == t2.end; }

Token newToken(Kind kind, u32 start, u32 end) { Token t = {.kind = kind, .start = start, .end = end}; return t; }


void tokenizer_test() {
	printf("RUNNING TESTS:\n");
	Tokenizer tokenizer = {
		.buffer = "()",
	};

	ASSERT(next_token(&tokenizer) == newToken(LEFT_PAREN, 0, 1));
	ASSERT(next_token(&tokenizer) == newToken(RIGHT_PAREN, 1, 2));

	printf("DONE\n");
}

#endif // _H_TOKENIZER_TEST
