/* 
* Generate a tokens from the OpenCL kernel
* It will detect __kernel, __global, int, float, void, __local
* @param token: the token to be generated
* @param kernel_string: the OpenCL kernel string
* @param len: the length of the kernel string
* @return: 0 if success, -1 if error
*/

#define TOKEN_LEN 6

// all possible tokens
static char *tokens[TOKEN_LEN] = {"__kernel", "__global", "int", "float", "void", "__local"};

int token_generate(char **token, char *kernel_string, int len);
