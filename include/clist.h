#include <stdbool.h>

#ifndef _CLIST_H_
#define	_CLIST_H_


typedef struct clist_e
{
	struct clist_e	*next,*prev;
	void			*p;
}clist_e;

typedef struct clist_t
{
	clist_e		*first,*last;
//	long		size;
}clist_t;


clist_t* clist_init(void);
void clist_destroy(clist_t *cl);

void clist_add(clist_t *cl,void* p);
void clist_remove(clist_t *cl,void* p);

void clist_insert_after(clist_t *cl,void* p,void* a);


void clist_push(clist_t *cl,void* p);
void* clist_pop(clist_t *cl);



#endif // _CLIST_H_
