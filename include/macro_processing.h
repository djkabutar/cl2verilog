/*
 * This function creates a table of macros from the kernel string.
 */
void create_macro_table(char *kernel_string);

/*
 * This function substitutes the macros in the kernel string with their
 * corresponding values.
 */
void substitute_macros(char *kernel_string);
