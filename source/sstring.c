#include "sstring.h"

#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

// #ifndef kMAX_CARRAY_GROW_HINT
// 	#define kMAX_CARRAY_GROW_HINT			100000
// #endif


/********************************/
/*{S}	Internals				*/
//	Functions(Private)
sstr_t* sstr_newPrealloc(uint32_t hint);

//	Variables(Private)
/*{E}	Internals				*/
/********************************/

// static inline bool carray_IsNULL(carray_t *a)
// {
// 	if(a==NULL)
// 	{
// 		kErrorAtLineInFuntion_NULL
// 		return true;
// 	}
// 	return false;
// }


// void sstr_init(void* value)
// {
// 	if(opt==eShouldShrink)
// 	{
// 		default_flags.shouldShrink=(bool*)value;
// 	}
// 	else if(opt==eIsExperimental)
// 	{
// 		default_flags.isExperimental=(bool*)value;
// 	}
// }


sstr_t* sstr_new(void)
{
	return sstr_newPrealloc(16);
}

sstr_t* sstr_new_allocsize(uint32_t size)
{
	return sstr_newPrealloc(size);
}

sstr_t* sstr_newPrealloc(uint32_t hint)
{
	sstr_t		*s;

	(void)hint;
	s=malloc(sizeof(sstr_t));
	s->count=0;
	return s;
}

void sstr_free(sstr_t **s)
{
	(void)s;
}

void sstr_destroy(sstr_t **s)
{
	(void)s;
}


void sstr_append(sstr_t *s,char* cstring)
{
	(void)s;
	(void)cstring;
}

void sstr_append_s(sstr_t *s,sstr_t *newStr)
{
	(void)s;
	(void)newStr;
}

void sstr_trunc(sstr_t *s,uint64_t len)
{
	(void)s;
	(void)len;
}

void sstr_remove(sstr_t *s,uint64_t offset,uint64_t len)
{
	(void)s;
	(void)offset;
	(void)len;
}
