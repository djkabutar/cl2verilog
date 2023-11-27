#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cl2verilog.h"

void remove_comments(char *kernel_string, int len) {
	// remove single line comments
	for (int i = 0; i < len; i++) {
		if (kernel_string[i] == '/' && kernel_string[i + 1] == '/') {
			// found a single line comment
			// remove it
			while (kernel_string[i] != '\n') {
				kernel_string[i] = ' ';
				i++;
			}
		}
	}

	// remove multiline comments
	for (int i = 0; i < len; i++) {
		if (kernel_string[i] == '/' && kernel_string[i + 1] == '*') {
			// found a multiline comment
			// remove it
			while (kernel_string[i] != '*' && kernel_string[i + 1] != '/') {
				kernel_string[i] = ' ';
				i++;
			}
		}
	}
}

int token_generate(struct tokend **token_array, char *kernel_string, int len) {
	int i, token_count = 0;

	// remove comments from the kernel string
	remove_comments(kernel_string, len);

	// from the given example of matmul in ../examples/matmul.cl
	// generate tokens for __kernel, __global, int, float, void, __local
	for (i = 0; i < len; i++) {
		// use naive search method to find predefined tokens
		// TODO: use more efficient search method
		// find out tokens from the tokens array in the header file

		for (int j = 0; j < TOKEN_LEN; j++) {
			if (strncmp(kernel_string + i, tokens[j], strlen(tokens[j])) == 0) {
				// found a token
				// store it in the token array
				*token_array = realloc(*token_array, sizeof(struct tokend) * (token_count + 1));
				token_array[token_count] = malloc(sizeof(struct tokend));
				token_array[token_count]->token = (char *) malloc(strlen(tokens[j]));
				memcpy(token_array[token_count]->token, tokens[j], strlen(tokens[j]));
				token_array[token_count]->token_len = strlen(tokens[j]);
				token_count++;
			}
		}
	}

	return token_count;
}
