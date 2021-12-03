#include <stdbool.h>
#include <stdlib.h>

#ifndef _CMEMORY_H_
#define	_CMEMORY_H_

#include <memory.h>
// #include <strings.h>
// #include <malloc.h>



inline void *memdup(const void *src, size_t n)
{
	void *dest;

	dest = malloc(n);
	if (dest == NULL)
		return NULL;
	return memcpy(dest, src, n);
}



#endif // _CMEMORY_H_
