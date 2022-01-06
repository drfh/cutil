/**
 * @file carray.c
 */
#include "global.h"
#include "carray.h"
#include "mymemmove.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef __DEBUG__
	#include <stdio.h>
#endif

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
static struct carray_flags_t	default_flags={.shouldShrink=false,.isExperimental=false,.sortAlgorithem=1,.compare=NULL,.keepSorted=0};
/*{E}	Internals				*/
/********************************/

void carray_init(carrayopt_e opt,const uintptr_t value)
{
	if(opt==eShouldShrink)
	{
		default_flags.shouldShrink=(bool)value;
	}
	else if(opt==eIsExperimental)
	{
		default_flags.isExperimental=(bool)value;
	}
	else if(opt==eSortAlgorithem)
	{
		default_flags.sortAlgorithem=(int)value;
	}
	else if(opt==eCompareFunction)
	{
		default_flags.compare=(int(*)(const void*,const void*))(value);
	}
	else if(opt==eKeepSorted)
	{
		default_flags.keepSorted=(int)value;
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

	a=malloc(sizeof(carray_t));
	a->count=0;
	a->allocated=hint;
	a->inc=kCARRAY_DEFAULT_PREALLOC;

	a->flags.shouldShrink=default_flags.shouldShrink;
	a->flags.isExperimental=default_flags.isExperimental;
	a->flags.sortAlgorithem=default_flags.sortAlgorithem;
	a->flags.compare=(int(*)(const void*,const void*))default_flags.compare;
	a->ptr=(void**)malloc(sizeof(void*)*hint);
	return a;
}

void carray_growHint(carray_t *a,uint32_t increase)
{
	assert(increase != 0);
	assert(increase < kMAX_CARRAY_GROW_HINT);
	a->inc=increase;
}

carray_t* carray_newfrom_vector(const void* v[],const int count)
{
	carray_t		*a=carray_new_allocsize(count);

	for(int i=0;i<count;i++)
		carray_add(a, (void*)v[i]);
	return a;
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
			free((*a)->ptr[t-1]);
			t--;
		}
	}
	free(*a);
	*a=NULL;
}

void carray_add(carray_t *a,void* p)
{
	if(a==NULL)
	{
		return;
	}
	// If there is not enough space in the memory bucket get a bigger one.
	if(a->count==a->allocated)
	{
		a->allocated+=a->inc;
		a->ptr=realloc(a->ptr,sizeof(void*)*a->allocated);
	}

	a->ptr[a->count]=p;
	a->count++;

	if(a->flags.keepSorted==1)
	{
		carray_sort(a,NULL);
	}
}
/*
void carray_addPtr(carray_t *a,void* ptr)
{
	if(a==NULL)
	{
		return;
	}
	// If there is not enough space in the memory bucket get a bigger one.
	if(a->count==a->allocated)
	{
		a->allocated+=a->inc;
		a->ptr=realloc(a->ptr,sizeof(void*)*a->allocated);
	}

	a->ptr[a->count]=ptr;
	a->count++;

	if(a->flags.keepSorted==1)
	{
		carray_sort(a,NULL);
	}
}
*/
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
		//assert(index >= a->count, "Index %ld beyond limit: %ld\n",index,a->count);
		return;
	}
	a->ptr[index]=NULL;
	if(index!=a->count-1)
	{
		void*	src=(void*)((uintptr_t)a->ptr+((index+1)*sizeof(void*)));
		void*	dest=(void*)((uintptr_t)a->ptr+(index*sizeof(void*)));

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
			void*	temp=(a->ptr[index1]);
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
		void*		temp;
		uintptr_t	dest;
		uintptr_t	p;

		if(from<to)
		{
			temp=(a->ptr[from]);
			dest=(uintptr_t)(a->ptr)+(sizeof(uintptr_t) * from);
			p=((uintptr_t)dest + sizeof(uintptr_t));

			memmove((void*)dest,(void*)p,(to-from) * sizeof(void*));
			a->ptr[to]=(void*)temp;
		}
		else if(to<from)
		{
			temp=(a->ptr[to]);
			dest=(uintptr_t)(a->ptr)+(sizeof(uintptr_t) * to);
			p=(uintptr_t)(dest+sizeof(uintptr_t));

			memmove((void*)dest,(void*)p,(from-to)*sizeof(uintptr_t));
			a->ptr[from]=temp;
		}
	}
}

void carray_sort(carray_t *arr,int (*compare)(const void*,const void*))
{
	fprintf(stderr,"int (*compare)(const void*,const void*) = %lu\n",(uintptr_t)compare);
	if(compare==NULL)
	{
		fprintf(stderr,"arr->flags.compare = %lu\n",(uintptr_t)(int (*)(const void*,const void*))arr->flags.compare);
		if(arr->flags.compare!=NULL)
		{
			carray_sort_selection(arr,arr->flags.compare);
		}
		else
		{
			fprintf(stderr,"Error: can't sort without (*compare(const void*,const void*)) function\n");
		}
	}
	else
	{
		carray_sort_selection(arr,compare);
	}
}

void carray_sort_selection(carray_t *arr,int (*compare)(const void*,const void*))
{
	size_t		n=carray_count(arr);
	size_t		i,j,position;

	for(i=0;i<(n-1);i++)
	{
		position=i;

		for(j=i+1;j<n;j++)
		{
			if(compare(carray_PtrAtindex(arr,j),carray_PtrAtindex(arr,position))<0)
				position=j;
		}
		carray_swap(arr,position,i);
	}
}

void carray_sort_insertion(carray_t *arr,int (*compare)(const void*,const void*))
{
	size_t		n=carray_count(arr);
	size_t		i;
	(void)compare;

	for (i = 1; i < n; i++) // finding minimum element (n-1) times
	{
		void*	temp=carray_PtrAtindex(arr,i);
		int		hole=i;

		while(hole>0 && strcmp(carray_PtrAtindex(arr,hole-1),temp)>0)
		{
			hole--;
		}
		printf("for(c): %ld\n",i);
		// temp = carray_PtrAtindex(a,c);
		carray_MoveTo(arr,hole,i-1);
	}
}
