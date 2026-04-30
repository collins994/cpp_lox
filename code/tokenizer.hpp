#ifndef _H_TOKENIZER
#define _H_TOKENIZER
enum Kind {
	// single character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
	// One or two character tokens.
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,
	// 
	END_OF_FILE, INVALID,
};

struct Token {
	Kind kind;
	u32 start;
	u32 end;
};

struct Tokenizer {
	const char *buffer;
	u32 count; // number of bytes in the source code
	u32 index; // index into the source code for the next character
};

// returns 0 if there's no more characters in the buffer
char tokenizer_peek(Tokenizer *tokenizer){
	if(tokenizer->index >= tokenizer->count) {
		return 0;
	}
	return tokenizer->buffer[tokenizer->index];
}

Token tokenizer_next_token(Tokenizer* tokenizer) {
	// skip whitespace between tokens
	for(;;) {
		char next_character = tokenizer->buffer[tokenizer->index];
		if (((next_character != ' ') && (next_character != '\t')) || (tokenizer->index >= tokenizer->count)) break; // break if we get to a non-space character or the end of input
		tokenizer->index++;
	}
	Token next_token = {.kind = INVALID, .start=tokenizer->index, .end=0};

	// peek to make sure there is a character before reading it
	if (tokenizer_peek(tokenizer) == 0) {
		next_token.kind = END_OF_FILE;
		next_token.end = tokenizer->index;
		return next_token;
	}


	char next_character = tokenizer->buffer[tokenizer->index];
	tokenizer->index += 1;
	switch (next_character) {
		case '(': { next_token.kind = LEFT_PAREN; } break;
		case ')': { next_token.kind = RIGHT_PAREN; } break;
		case '{': { next_token.kind = LEFT_BRACE; } break;
		case '}': { next_token.kind = RIGHT_BRACE; } break;
		case ',': { next_token.kind = COMMA; } break;
		case '.': { next_token.kind = DOT; } break;
		case '-': { next_token.kind = MINUS; } break;
		case '+': { next_token.kind = PLUS; } break;
		case ';': { next_token.kind = SEMICOLON; } break;
		case '/': { next_token.kind = SLASH; } break;
		case '*': { next_token.kind = STAR; } break;
		case '!': { 
			next_token.kind = BANG; 
			if (tokenizer_peek(tokenizer) == '='){ 
				tokenizer->index += 1; 
				next_token.kind = BANG_EQUAL; 
			}
		} break;
		case '=': { 
			next_token.kind = EQUAL; 
			if(tokenizer_peek(tokenizer) == '=') {
				tokenizer->index += 1; 
				next_token.kind = EQUAL_EQUAL; 
			}
		} break;
		case '>': { 
			next_token.kind = GREATER; 
			if(tokenizer_peek(tokenizer) == '=') {
				tokenizer->index += 1; 
				next_token.kind = GREATER_EQUAL; 
			}
		} break;
		case '<': { 
			next_token.kind = LESS; 
			if(tokenizer_peek(tokenizer) == '=') {
				tokenizer->index += 1; 
				next_token.kind = LESS_EQUAL; 
			}
		} break;
	}

	next_token.end = tokenizer->index;
	return next_token;
}

/* 
	read the file into tokenizer.buffer
	returns 0 on success
	returns -1 if it fails
*/
int tokenizer_init(Tokenizer *tokenizer, const char *file_path){
	errno = 0;
	FILE *source_file;
	long file_size;

	if (
		((errno = fopen_s(&source_file, file_path, "rb")) != 0) || // open the file
		(fseek(source_file, 0, SEEK_END) != 0 || (file_size = ftell(source_file)) < 0 || (fseek(source_file, 0, SEEK_SET)) != 0) || // get the file size
		((tokenizer->buffer = (char *)malloc(file_size + 1)) == NULL) // allocate memory for the tokenizer.buffer 
	) { return -1; }

	memset((void *)tokenizer->buffer, 0, (size_t)(file_size + 1));
	if (fread((void *)tokenizer->buffer, sizeof(char), file_size, source_file) != file_size){ return -1; }

	// TODO(collins): initialize the tokenizer fields in one place
	tokenizer->count = file_size;
	fclose(source_file); // close the file 
	return file_size;
}


/* 
	free the tokenizer.buffer
*/
void tokenizer_destroy(Tokenizer *tokenizer) {
	free((void *)tokenizer->buffer);
}
#endif // _H_TOKENIZER
