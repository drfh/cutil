#include "carray.h"

//#include <stdio.h>
#include <assert.h>
#include <string.h>

#ifndef kMAX_CARRAY_GROW_HINT
	#define kMAX_CARRAY_GROW_HINT			100000
#endif


/********************************/
/*{S}	Internals				*/
//	Functions(Private)
carray_t* carray_newPrealloc(uint32_t hint);
// static inline bool carray_IsNULL(carray_t *a);
void carray_destroyClean(carray_t **a,bool clean);

//	Variables(Private)
struct carray_flags_t	default_flags={.shouldShrink=false,.isExperimental=false};
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


void carray_init(carrayopt_e opt,void* value)
{
	if(opt==eShouldShrink)
	{
		default_flags.shouldShrink=(bool*)value;
	}
	else if(opt==eIsExperimental)
	{
		default_flags.isExperimental=(bool*)value;
	}
}


carray_t* carray_new(void)
{
	return carray_newPrealloc(kCARRAY_DEFAULT_PREALLOC);
}

carray_t* carray_new_allocsize(uint32_t size)
{
	return carray_newPrealloc(size);
}

carray_t* carray_newPrealloc(uint32_t hint)
{
	carray_t		*a;

	a=DHMALLOC(sizeof(carray_t));
	a->count=0;
	a->allocated=hint;
	a->inc=kCARRAY_DEFAULT_PREALLOC;

	a->flags.shouldShrink=default_flags.shouldShrink;
	a->flags.isExperimental=default_flags.isExperimental;
	a->ptr=(void**)DHMALLOC(sizeof(void*)*hint);
	return a;
}

void carray_growHint(carray_t *a,uint32_t increase)
{
	assert(increase != 0);
	assert(increase < kMAX_CARRAY_GROW_HINT);
}


void carray_free(carray_t **a)
{
	carray_destroyClean(a,true);
}

void carray_destroy(carray_t **a)
{
	carray_destroyClean(a,false);
}

inline void carray_destroyClean(carray_t **a,bool clean)
{
	if(*a==NULL)
	{
		return;
	}
	if(clean==true)
	{
		while((*a)->count)
		{
			carray_removeIndex(*a,(*a)->count-1);

		}
	}
	else
	{
		int		t=(*a)->count;
		while(t)
		{
			DHFREE((*a)->ptr[t-1]);
			t--;
		}
	}
	DHFREE(*a);
	*a=NULL;
}

void carray_add(carray_t *a,void* ptr)
{
	if(a==NULL)
	{
		return;
	}
	// If there is not enough space in the memory bucket get a bigger one.
	if(a->count==a->allocated)
	{
		a->allocated+=kCARRAY_DEFAULT_PREALLOC;
		a->ptr=DHREALLOC(a->ptr,sizeof(void**)*kCARRAY_DEFAULT_PREALLOC);
	}

	a->ptr[a->count]=ptr;
	a->count++;
}

void carray_insert(carray_t *a,void* ptr,uint64_t index)
{
	memmove((void*)((uint64_t)(a->ptr)+index+1),(void*)((uint64_t)(a->ptr)+index),sizeof(void*)*(a->count-index));
	a->ptr[index]=ptr;
}


void carray_remove(carray_t *a,void* ptr)
{
	uint64_t		i;
	if((i=carray_IndexOfPtr(a,ptr))!=0xFFFFFFFFFFFFFFFF)
		carray_removeIndex(a,i);
}

void carray_removeIndex(carray_t *a,uint64_t index)
{
	if(index >= a->count)
	{
		//fprintf(stderr,"%s (%d)[%s]: Index %ld beyond limit: %ld\n",__FILE__,__LINE__,__FUNCTION__,index,a->count);
		return;
	}
	a->ptr[index]=NULL;
	if(index!=a->count-1)
	{
		void*	src=(void*)((uint64_t)(a->ptr)+((index+1)*sizeof(void*)));
		void*	dest=(void*)((uint64_t)(a->ptr)+(index*sizeof(void*)));

		memmove(dest,src,(a->count-index)*sizeof(void*));
	}
	// Reduce the size of the bucket if it is too big
	if(a->flags.shouldShrink)
	{
		if((a->count+a->inc) < a->allocated)
		{
			a->ptr=realloc(a->ptr,a->allocated-a->inc);
			a->allocated-=a->inc;
		}
	}
	a->count--;
}

void* carray_PtrAtindex(carray_t *a,uint64_t index)
{
	assert(index < a->count);
	return a->ptr[index];
//	return NULL;
}
uint64_t carray_IndexOfPtr(carray_t *a,void* ptr)
{
	uint64_t	i=0;

	assert(ptr != NULL);
	while(a->count>i)
	{
		if(a->ptr==ptr)
			return i;
		i++;
	}
	return -1;
}

uint64_t carray_count(carray_t *a)
{
	if(a==NULL)
	{
		return 0;
	}
	return a->count;
}

void carray_swap(carray_t *a,uint64_t index1,uint64_t index2)
{
	if(a==NULL)
	{
		return;
	}
	if(index1<a->count)
	{
		if(index2<a->count)
		{
			uint64_t	temp=(uint64_t)(a->ptr[index1]);
			a->ptr[index1]=a->ptr[index2];
			a->ptr[index2]=(void*)temp;
		}
	}
}

void carray_MoveTo(carray_t *a,uint64_t from,uint64_t to)
{
	if(a==NULL)
	{
		return;
	}
	if(from==to)
	{
		return;
	}
	if(from<a->count && to<a->count)
	{
		if(from<to)
		{
			uint64_t	temp=(uint64_t)(a->ptr[from]);
			uint64_t	dest=((uint64_t)(a->ptr)+(sizeof(void*) * from));

			memmove((void*)dest,(void*)(dest+ sizeof(void*)),(to-from) * sizeof(void*));
			a->ptr[to]=(void*)temp;
		}
		else if(from>to)
		{
			uint64_t	temp=(uint64_t)(a->ptr[to]);

			uint64_t	dest=((uint64_t)(a->ptr)+(sizeof(void*) * to));
			uint64_t	p=dest+sizeof(void*);

			memmove((void*)dest,(void*)p,(from-to)*sizeof(void*));
			a->ptr[from]=(void*)temp;
		}
	}
}
