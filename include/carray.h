/**
 * @Author: david
 * @Date:   2021-12-03T19:14:15-05:00
 * @Last modified by:   david
 * @Last modified time: 2021-12-29T12:52:34-05:00
 */



#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#ifndef _CARRAY_H_
#define	_CARRAY_H_

#define	kCARRAY_VERSION					"1.0.0"
#define	kCARRAY_DEFAULT_PREALLOC		32


/********************************/
/*{S}	Experimental			*/
struct cbucket_t
{
	struct cbucket_t	*next;
	struct cbucket_t	*prev;
	void*		*ptr;
	uint16_t	count;
};
typedef	struct cbucket_t	cbucket_t;
/*{E}	Experimental			*/
/********************************/

// Using an enum declaration for no reason other that to finaly use it
// Prabably would be a little faster with bitmask.
// Might macro compile switch that later
enum ca_opt{
	eShouldShrink,
	eIsExperimental
};
typedef	enum ca_opt		carrayopt_e;

typedef struct carray_flags_t
{
	bool	shouldShrink;
	bool	isExperimental;
}carray_flags_t;

typedef struct
{
	uint64_t	count;
	uint64_t	allocated;
	uint64_t	inc;

	carray_flags_t	flags;
	void*		*ptr;
	// linked list buckets
	// cbucket_t	*first;
	// cbucket_t	*last;
}carray_t;

/**
 * Initializes the global carray behaviour with options
 * @param opt	IP address to bind to. (NULL = all interfaces)
 *
 * @see ca_opt carray_t
 */
void carray_init(carrayopt_e opt,void* value);

carray_t* carray_new(void);
carray_t* carray_new_allocsize(uint32_t size);
void carray_growHint(carray_t *a,uint32_t increase);

void carray_free(carray_t **a);
void carray_destroy(carray_t **a);

void carray_add(carray_t *a,void* p);
void carray_addPtr(carray_t *a,void* ptr);
void carray_insert(carray_t *a,void* ptr,uint64_t index);

void carray_remove(carray_t *a,void* ptr);
void carray_removeIndex(carray_t *a,uint64_t index);

void* carray_PtrAtindex(carray_t *a,uint64_t index);
uint64_t carray_IndexOfPtr(carray_t *a,void* ptr);

uint64_t carray_count(carray_t *a);
void carray_swap(carray_t *a,uint64_t index1,uint64_t index2);
void carray_MoveTo(carray_t *a,uint64_t from,uint64_t to);

void carray_sort_selection(carray_t *a,int sort_func(void*,void*));
void carray_sort_insertion(carray_t *arr,int sort_func(void*,void*));

#define carray_length(a)		carray_count(a)


#endif // _CARRAY_H_
