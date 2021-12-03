#include <stdint.h>
#include <stdbool.h>

#ifndef _SSTRING_H_
#define	_SSTRING_H_

#define	kSSTRING_VERSION				"1.0.0"
#define	kSSTRING_DEFAULT_PREALLOC		32


/********************************/
/*{S}	Experimental			*/
/*{E}	Experimental			*/
/********************************/

// Using an enum declaration for no reason other that to finaly use it
// Prabably would be a little faster with bitmask.
// Might macro compile switch that later
typedef	enum {
	eShouldShrink,
	eIsExperimental
}sstropt_e;

typedef struct
{
	bool	shouldShrink;
	bool	isExperimental;
}sstr_flags_t;

typedef struct
{
	uint64_t	count;
	uint8_t		s;
}sstr_t;


// void sstr_init(sstropt_e opt,void* value);

sstr_t* sstr_new(void);
sstr_t* sstr_new_allocsize(uint32_t size);

void sstr_free(sstr_t **a);
void sstr_destroy(sstr_t **a);

void sstr_append(sstr_t *s,char* cstring);
void sstr_append_s(sstr_t *s,sstr_t *newStr);

void sstr_trunc(sstr_t *s,uint64_t len);

void sstr_remove(sstr_t *s,uint64_t offset,uint64_t len);

#endif // _SSTRING_H_
