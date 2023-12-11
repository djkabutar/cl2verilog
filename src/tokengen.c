#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int token_push(struct tokend **token_array, char *token, int token_len, int token_count) {
	// store it in the token array
	*token_array = realloc(*token_array, sizeof(struct tokend) * (token_count + 1));
	token_array[token_count] = malloc(sizeof(struct tokend));
	token_array[token_count]->token = (char *) malloc(token_len + 1);
	memset(token_array[token_count]->token, 0, token_len + 1);
	memcpy(token_array[token_count]->token, token, token_len);
	token_array[token_count]->token_len = token_len;
	token_count++;

	return token_count;
}

int check_token(char *kernel_string, char special_char, int i, int len, int token_count, struct tokend **token_array) {
	if (kernel_string[i] == special_char) {
		token_count = token_push(token_array, kernel_string + i, 1, token_count);
	}

	return token_count;
}

int token_generate(struct tokend **token_array, char *kernel_string, int len) {
	int i, j = 0, token_count = 0;

	// remove comments from the kernel string
	remove_comments(kernel_string, len);

	// from the given example of matmul in ../examples/matmul.cl
	for (i = 0; i < len; i++) {
		j = i;
		// check for alphanumeric characters and underscore
		while (isalpha(kernel_string[j]) || isdigit(kernel_string[j]) || kernel_string[j] == '_') {
			j++;
		}

		if (j != i) {
			token_count = token_push(token_array, kernel_string + i, j - i, token_count);
			i = j - 1;
			continue;
		}

		// check for brackets, semicolon, comma, equal sign
		token_count = check_token(kernel_string, '(', i, len, token_count, token_array);
		token_count = check_token(kernel_string, ')', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '[', i, len, token_count, token_array);
		token_count = check_token(kernel_string, ']', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '{', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '}', i, len, token_count, token_array);
		token_count = check_token(kernel_string, ';', i, len, token_count, token_array);
		token_count = check_token(kernel_string, ',', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '=', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '*', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '/', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '-', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '&', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '<', i, len, token_count, token_array);
		token_count = check_token(kernel_string, '>', i, len, token_count, token_array);

	}

	return token_count;
}
