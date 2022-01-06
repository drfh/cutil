/**
 * @file clist.c
 */

#include "global.h"
#include "clist.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>


clist_t* clist_init(void)
{
	clist_t	*p=malloc(sizeof(clist_t));
	p->first=NULL;
	p->last=NULL;
	return p;
}

void clist_destroy(clist_t *cl)
{

	free(cl);
}


void clist_add(clist_t *cl,void* p)
{
	cl->last->next=p;
}
