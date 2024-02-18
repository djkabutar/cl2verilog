#include <stdint.h>
#include <errno.h>

#define TOKEN_LEN 6

/* all possible keywords */
static char **keywords = {"__kernel", "__global", "int", "float", "void", "__local"};

struct tokend {
	char *token;
	uint8_t token_len;
};

struct macro {
	char *name;
	char *value;
	char *args;
	uint8_t args_num;
	uint8_t value_len;
	uint8_t name_len;
	uint8_t args_len;
};

/* 
* Generate a tokens from the OpenCL kernel
* @param token: the token to be generated
* @param kernel_string: the OpenCL kernel string
* @param len: the length of the kernel string
* @return: 0 if success, -1 if error
*/
int token_generate(struct tokend **token_array, char *kernel_string, int len);

/*
 * Macro substitution
 * @param kernel_string: the OpenCL kernel string
 * @param len: the length of the kernel string
 * @return: 0 if success, -1 if error
 */
int macro_substitution(char *kernel_string, int len);

/*
 * Hashing Function
 * @param token: the token to be hashed
 * @param len: the length of the token
 * @return: the hash value of the token
 */
uint32_t hashfunc(const char *token, int len);

/*
 * Hashing Function of 16-Bit
 * @param token: the token to be hashed
 * @return: the hash value of the token
 */
uint16_t hashfunc16(const char *token);
