#include "global.h"
#include "cstack.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>


cstack_t* cstack_init(void)
{
	cstack_t	*p=malloc(sizeof(cstack_t));

	return p;
}
