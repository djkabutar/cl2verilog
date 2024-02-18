/*
 * This module will generate symbol table for the macros and substitue
 * them in the kernel string.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <regex.h>

#include "cl2verilog.h"

#define HASHSIZE16 (1 << 16)

struct hash_table {
	uint32_t hash;
	unsigned int index;
};

struct macro macro_table[HASHSIZE16] = {0};

/* Gets the macro name and its value from the kernel string */ 
void create_macro_table(char *kernel_string) {
	char *macro_name;
	char *macro_value;
	char *token;
	char *saveptr;
	char *kernel_string_copy;
	int i = 0;

	kernel_string_copy = (char *)malloc(strlen(kernel_string) + 1);
	strcpy(kernel_string_copy, kernel_string);

	token = strtok_r(kernel_string_copy, " ", &saveptr);
	while (token != NULL) {
		if (strstr(token, "#define") != NULL) {
			macro_name = strtok_r(NULL, " ", &saveptr);
			macro_value = strtok_r(NULL, " ", &saveptr);

			uint16_t h = hashfunc16(macro_name);

			macro_table[h].name_len = strlen(macro_name);
			macro_table[h].value_len = strlen(macro_value);

			macro_table[h].name = (char *)malloc(macro_table[h].name_len + 1);
			macro_table[h].value = (char *)malloc(macro_table[h].value_len + 1);

			memcpy(macro_table[h].name, macro_name, macro_table[h].name_len);
			memcpy(macro_table[h].value, macro_value, macro_table[h].value_len);
			i++;
		}
		token = strtok_r(NULL, " ", &saveptr);
	}
	macro_table.num_macros = i;

	/* Free the memory */
	free(kernel_string_copy);
}

/* Substitutes the macros in the kernel string */
void substitute_macros(char *kernel_string) {
	// TODO: Implement this function
}
