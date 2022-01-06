/**
 * @file cstack.h
 */

#ifndef _CSTACK_H_
#define	_CSTACK_H_


typedef struct cstack
{
	struct cstack_t		*next,*prev;

//	long		size;
	void		*p;
}cstack_t;


cstack_t* cstack_init(void);
void cstack_destroy(cstack_t *p);

void cstack_push(void* p);
void* cstack_pop(void);



#endif // _CSTACK_H_
