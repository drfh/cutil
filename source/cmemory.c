/**
 * @file cmemory.c
 */

#include "global.h"

#include <stdlib.h>
#include <memory.h>

// #include <strings.h>
// #include <malloc.h>
#include "cmemory.h"

void* memdup(const void *src, size_t n)
{
	void *dest;

	dest = malloc(n);
	if (dest == NULL)
		return NULL;
	return memcpy(dest, src, n);
}
