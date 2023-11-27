#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cl2verilog.h"

int print_tokens(struct tokend** token_array, int tokens_count)
{
	for (int i = 0; i < tokens_count; i++) {
		printf("Token: %s\n", token_array[i]->token);
		printf("Token Len: %d\n", token_array[i]->token_len);
	}
	return 0;
}

int main(int argc, char** argv)
{
	FILE* fp = NULL;
	char* line = NULL;
	size_t len = 0;
	char* kernel = NULL;
	struct tokend* token_array = NULL;
	int tokens_count;
	int total_len_kernel = 0;
	int ret = 0;

	// get the file path of kernel from the command line
	// if no argument is given, print error message and exit
	if (argc < 2) {
		printf("Usage: %s <kernel.cl>\n", argv[0]);
		ret = 1;
		goto err_file;
	}

	// open file and check if it is opened successfully
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("Error");
		ret = 1;
		goto err_file;
	}

	// read the file line by line into kernel
	while (getline(&line, &len, fp) != -1) {
		total_len_kernel += len;
		kernel = (char*) realloc(kernel, total_len_kernel + 1);
		strcat(kernel, line);
	}

	// generate tokens from kernel
	// and store into tokens
	tokens_count = token_generate(&token_array, kernel, strlen(kernel));
	if (tokens_count < 1) {
		printf("Error: cannot generate tokens\n");
		ret = 1;
		goto err_token_gen;
	}

	// print tokens
	print_tokens(&token_array, tokens_count);

	// if (fp != NULL)
	// 	fclose(fp);

err_token_gen:
	// free memory
	for (int i = 0; i < tokens_count; i++) {
		free(token_array[i].token);
	}
	free(token_array);
	free(kernel);
	free(line);

err_file:
	if (ret)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
