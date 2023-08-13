#define TOKEN_LEN 6

// all possible tokens
static char *tokens[TOKEN_LEN] = {"__kernel", "__global", "int", "float", "void", "__local"};

struct tokend {
	char *token,
	uint32_t pos
};

/* 
* Generate a tokens from the OpenCL kernel
* It will detect __kernel, __global, int, float, void, __local
* @param token: the token to be generated
* @param kernel_string: the OpenCL kernel string
* @param len: the length of the kernel string
* @return: 0 if success, -1 if error
*/
int token_generate(struct tokend *token, char *kernel_string, int len);
