/*
 * This file contains the hash function used to hash the keys.
 * Function will return 32 bit hash value.
 */

#include <math.h>
#include <stdint.h>

#include "cl2verilog.h"

#define HASHSIZE (1 << 32)
#define HASHSIZE16 (1 << 16)

uint32_t hashfunc(const char *key, int len)
{
	uint32_t hash, i;
	for(hash = i = 0; i < len; ++i)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return (hash % HASHSIZE);
}

uint16_t hashfunc16(const char *key)
{
	int hash, i;
	for (int c = *key++; c != 0; c = *key++) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return (hash % HASHSIZE16);
}
