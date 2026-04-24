#ifndef _H_TOKENIZER
#define _H_TOKENIZER
enum Kind {
	// single character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
};

struct Token {
	Kind kind;
	u32 start;
	u32 end;
};

struct Tokenizer {
	const char *buffer;
	u32 index; // index into the source code for the next character
};

Token next_token(Tokenizer* tokenizer) {
	Token token = {.start = 0, .end=2};
	return token;
}

/* 
	read the file into tokenizer.buffer
	returns the number of bytes in the source file if succesful
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
