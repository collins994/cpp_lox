#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define u32 uint32_t
#include "tokenizer.hpp"

// read_file reads the file at file_path into tokenizer.source_buffer
// on success, it returns the number of bytes read 
// on failure, it returns -1 and set the error code to errno
long read_file(Tokenizer *tokenizer, const char *file_path) {
	errno = 0;
	FILE *source_file;
	long file_size;

	// open the file, errno is automatically set by fopen_s
	if ((errno = fopen_s(&source_file, file_path, "rb")) != 0) { return -1; }

 	// get the file size, errno is set by ftell or fseek
	if ((fseek(source_file, 0, SEEK_END)) != 0 || (file_size = ftell(source_file)) < 0 || (fseek(source_file, 0, SEEK_SET)) != 0 ) {return -1; }

	// allocate memory for the tokenizer.buffer - an extra byte for the terminating null byte
	if ((tokenizer->source_buffer = (char *)malloc(file_size + 1)) == NULL) { return -1; }

	// read the file into tokenizer.source_buffer
	memset((void *)tokenizer->source_buffer, 0, (size_t)(file_size + 1));
	if (fread((void *)tokenizer->source_buffer, sizeof(char), file_size, source_file) != file_size){ return -1; }

	fclose(source_file); // close the file 
	return file_size;
}


int main(int argc, char *argv[]) {
	Tokenizer tokenizer = {};

	if (argc < 2) {
		printf("USAGE: lox.exe <file>\n");
		exit(EXIT_FAILURE);
	}

	// read from file 
	if (read_file(&tokenizer, argv[1]) == -1) {
		printf("ERROR: unable to read file, code : %d\n", errno);
		// printf("ERROR: tokenizer.source_buffer == NULL after read_file");
		exit(EXIT_FAILURE);
	}

	free((void *)tokenizer.source_buffer);
}
