#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define u32 uint32_t
#include "tokenizer.hpp"
#include "common.hpp"

int main(int argc, char *argv[]) {
	Tokenizer tokenizer = {};

	if (argc < 2) {
		printf("USAGE: lox.exe <file>\n");
		exit(EXIT_FAILURE);
	}
	int byte_count; 
	if ((byte_count = tokenizer_init(&tokenizer, argv[1])) == -1) {
		printf("ERROR: unable to read file, code : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	Token token = next_token(&tokenizer);
	tokenizer_destroy(&tokenizer);
}
