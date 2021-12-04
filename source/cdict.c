#include "cdict.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <memory.h>

// #include "carray.h"
#include "cmemory.h"

//	Variables(Private)
//struct cdict_flags_t	default_flags={.shouldShrink=false,.isExperimental=false};
/*{E}	Internals				*/
/********************************/
uint32_t cdict_get_kindex(cdict_t *d,const char* key);



void cdict_init(void)
{
	;
}

cdict_t* cdict_new(void)
{
	return cdict_new_allocsize(6);
}

cdict_t* cdict_new_allocsize(uint32_t size)
{
	cdict_t*	p=malloc(sizeof(cdict_t));

	if(p)
	{
		p->count=0;
		p->allocated=0;
		p->inc=1;
		p->state=err_NOERROR;

		p->flags.add_if_unknown=true;
		p->flags.copy_keys=false;
		p->flags.free_val_on_set=true;

		p->array=(keyval_t**)malloc(sizeof(*p->array)*size);
		for(uint32_t i=0;i<size;i++)
			p->array[i]=0;
	}
	return p;
}

int cdict_size(cdict_t *d)
{
	assert(d != NULL);
	if(d!=NULL)
		return d->count;
	return 0;
}

/*
void cdict_growHint(cdict_t *d,uint32_t increase)
{
	;
}
*/

inline void cdict_empty(cdict_t *d)
{
	for(uint64_t i=0;i<d->count;i++)
	{
		keyval_t	*kv=d->array[i];

		// printf("(%lu)K: %s   V: %s\n",i,kv->k,(char*)kv->v);
		free(kv->k);
		free(kv->v);
		free(kv);
		d->array[i]=NULL;
	}
	d->count=0;
}

void cdict_free(cdict_t **dict)
{
	assert(dict != NULL);
	cdict_t		*d=*dict;

	cdict_empty(d);
	// keyval_t	*kv;
	// for(uint64_t i=0;i<d->count;i++)
	// {
	// 	kv=d->array[i];
	// 	printf("(%lu)K: %s   V: %s\n",i,kv->k,(char*)kv->v);
	// 	free(kv->k);
	// 	free(kv->v);
	// 	free(kv);
	// 	d->array[i]=NULL;
	// }
	// d->count=0;
	free(d->array);
	free(d);
	*dict=NULL;
}

void cdict_destroy(cdict_t **d)
{
	cdict_free(d);
	free(d);
}

void cdict_reset(cdict_t *d)
{
	if(d->state==err_NOTFOUND)
		d->state=err_NOERROR;
	else if(d->state==err_NOTADDED)
		d->state=err_NOERROR;
}

inline void cdict_grow(cdict_t *d,uint32_t hint)
{
	assert(d != NULL);
	if(d->allocated<=d->count)
	{
		d->allocated+=hint;
		d->array=realloc(d->array,sizeof(*d->array)*d->allocated);
	}
}

inline void cdict_add_kv(cdict_t *d,keyval_t *kv)
{
	cdict_grow(d,1);
	d->array[d->count]=kv;
	d->count++;
}

//inline void cdict_add(cdict_t *d,char* key,void* ptr,type_t t)
inline void cdict_add(cdict_t *d,const char* key,void* ptr)
{
	keyval_t	*kv=malloc(sizeof(*kv));

	kv->k=strdup(key);
	kv->v=ptr;
	cdict_add_kv(d,kv);
}

void cdict_remove(cdict_t *d,char* key)
{
	assert(d != NULL);
	if(key == NULL)
	{
		return;
	}
	keyval_t	*kv;
	for(uint32_t i=0;i<d->count;i++)
	{
		kv=d->array[i];
		if(strcmp(key,kv->k)==0)
		{
			free(kv->v);
			free(kv);
			d->array[i]=NULL;
			if(i!=d->count-1)
			{
				void*	src=(void*)((uint64_t)(d->array)+((i+1)*sizeof(void*)));
				void*	dest=(void*)((uint64_t)(d->array)+(i*sizeof(void*)));

				memmove(dest,src,(d->count-i)*sizeof(void*));
			}
			d->count--;
		/*
			// Reduce the size of the bucket if it is too big
			if(a->flags.shouldShrink)
			{
				if((a->count+a->inc) < a->allocated)
				{
					a->ptr=realloc(a->ptr,a->allocated-a->inc);
					a->allocated-=a->inc;
				}
			}
		*/
		}
	}
}

inline uint32_t cdict_get_kindex(cdict_t *d,const char* key)
{
	assert(d != NULL);
	keyval_t	*kv;

	d->state=err_NOERROR;
	for(uint32_t i=0;i<d->count;i++)
	{
		kv=d->array[i];
		if(strcmp(key,kv->k)==0)
			return i;
	}
	d->state=err_NOTFOUND;
	return -1;
}

void* cdict_get_vfork(cdict_t *d,char* key)
{
	uint32_t	i=cdict_get_kindex(d,key);
	if(d->state==err_NOERROR)
	{
		keyval_t	*kv=d->array[i];
		return kv->v;
	}
	return NULL;
}


// void cdict_set_vfork_o(cdict_t *d,char* key,void* v,bool copy)
//void cdict_set_vfork(cdict_t *d,char* key,void* v,type_t t)
void* cdict_set_vfork(cdict_t *d,const char* key,void* v)
{
	assert(d != NULL);
	uint32_t	i=cdict_get_kindex(d,key);
	void*		oldval=NULL;

	if(d->state==err_NOERROR)
	{
		//	Update old kv
		keyval_t	*kv=d->array[i];
		oldval=kv->v;

	//	if(kv->v != NULL)
	//		if(true==d->flags.free_val_on_set)
	//			free(kv->v);
		kv->v=v;
	}
	else if(d->state==err_NOTFOUND)
	{
		//	Add new kv
		if(d->flags.add_if_unknown==true)
			cdict_add(d,key,v);
		else
			d->state=err_NOTADDED;
		d->state=err_NOERROR;
	}
	// printf("(Set)%s: %p\n",key,(void*)v);
	return oldval;
}

void* cdict_set_v4k_dup(cdict_t *d,const char* key,void* v,const size_t size)
{
	assert(d != NULL);
	void	*oldval=NULL;
	void	*newval=memdup(v,size);

	oldval=cdict_set_vfork(d,key,newval);
	if(!oldval)
	{
		free(newval);
	}
	//	uint32_t	i=cdict_get_kindex(d,key);
	// if(d->state==err_NOERROR)
	// {
	// 	//	Update old kv
	// 	keyval_t	*kv=d->array[i];
	// 	oldval=kv->v;
	//
	// 	kv->v=newval;
	// }
	// else if(d->state==err_NOTFOUND)
	// {
	// 	//	Add new kv
	// 	if(d->flags.add_if_unknown==true)
	// 		cdict_add(d,key,newval);
	// 	else
	// 		d->state=err_NOTADDED;
	// 	d->state=err_NOERROR;
	// }
	// printf("(Set)%s: %p\n",key,(void*)newval);
	return oldval;
}
