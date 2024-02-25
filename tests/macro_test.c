#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>

#include <cl2verilog.h>

int main(int argc, char *argv[])
{
	/* get the filename from the argument */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *filename = argv[1];

	/* open the file */
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	struct stat st = {0};
	stat(filename, &st);

	/* read the file */
	char *kernel_string = malloc(st.st_size);
	if (kernel_string == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (fread(kernel_string, 1, st.st_size, fp) != st.st_size) {
		perror("fread");
		exit(EXIT_FAILURE);
	}

	macro_substitution(kernel_string, st.st_size);

	fprintf(stdout, "%s\n", kernel_string);

	/* close the file */
	if (fclose(fp) != 0) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	/* free allocated memory */
	free(kernel_string);
	return 0;
}
