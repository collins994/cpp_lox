#ifndef _H_TOKENIZER
#define _H_TOKENIZER

struct Token {
	u32 start;
	u32 end;
};

struct Tokenizer {
	const char *source_buffer;

	u32 index; // index into the source code for the next character
};

Token next_token(Tokenizer* tokenizer) {
	Token token = {.start = 0, .end=2};
	return token;
}

#endif // _H_TOKENIZER
