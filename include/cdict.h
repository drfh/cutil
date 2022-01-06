/**
 * @file cdict.h
 */
#ifndef _CDICT_H_
#define	_CDICT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#if 0
const int16_t		err_NOERROR		=0;
const int16_t		err_NOTFOUND	=-10;
const int16_t		err_NOTADDED	=-11;
//const int16_t		err_NOTFOUND	=-10;
#else
#define	err_NOERROR			0
#define	err_NOTFOUND		-10
#define	err_NOTADDED		-11
#endif
/*
typedef enum
{
	int_type,
	float_type,
	string_type,
	data_type,
	array_type,
	dict_type
}type_t;
typedef struct
{
	void*	v;
	type_t	t;
}value_t;
*/

typedef struct
{
	char*	k;
	void*	v;
}keyval_t;

typedef	struct
{
	uint64_t	count;
	uint64_t	allocated;
	uint64_t	inc;

	keyval_t	**array;

	int16_t		state;
	struct
	{
		bool	copy_keys;
		bool	free_val_on_set;
		bool	add_if_unknown;
	}flags;
}cdict_t;


/**
 * Initilization of the cdict background settings like flags that should be used when allocating and setting.
 *
 * @see cdict.h
 */
void cdict_init(void);

/**
 * A brief description. A more elaborate class description
 * @see cdict_t
 * @return A pointer to a cdict_t struct.
 */
cdict_t* cdict_new(void);

/**
 * Create a cdict_t* pointer with a preallocated array for key/values.
 * This is important for large dictionaries so that they don't need reallocations while adding keys.
 * @param size an integer of how many records to preallocate.
 * @see cdict_t
 * @see cdict_new()
 * @return A pointer to a cdict_t struct.
*/
cdict_t* cdict_new_allocsize(uint32_t size);
//void cdict_growHint(cdict_t *d,uint32_t increase);

/**
 * Gets the number of key/value pairs referanced in the dictionary parameter d
 * @param d The pointer to the dictionary record cdict_t
 * @see cdict_t
 * @see cdict_new()
 * @return size of the array holding the key/value elements.
*/
int cdict_size(cdict_t *d);

/**
 * a normal member taking two arguments and returning an integer value.
 * @param d The handle to the dictionary record cdict_t** that will be freed and set to NULL
 * @see cdict_t
*/
void cdict_empty(cdict_t *d);
void cdict_free(cdict_t **dict);
void cdict_destroy(cdict_t **d);

void cdict_reset(cdict_t *d);

//void cdict_add(cdict_t *d,char* key,void* ptr,type_t t);
//void cdict_add(cdict_t *d,char* key,void* ptr);
//void cdict_add_kv(cdict_t *d,keyval_t *kv);

void cdict_remove(cdict_t *d,char* key);

void* cdict_get_vfork(cdict_t *d,char* key);
#define	cdict_get_value_for_keyk(d,k)	cdict_set_vfork(d,k)
#define	cdict_get(d,k)					cdict_set_vfork(d,k)

void* cdict_set_vfork(cdict_t *d,const char* key,void* v);
#define	cdict_set(d,k,v)				cdict_set_vfork(d,k,v)
// #define	cdict_set_value_for_key(d,k,v)	cdict_set_vfork(d,k,v)


void* cdict_set_v4k_dup(cdict_t *d,const char* key,void* v,const size_t size);
#define	cdict_set_dup(d,k,v,s)			cdict_set_v4k_dup(d,k,v,s)
// #define	cdict_set_value_for_key(d,k,v)	cdict_set_vfork(d,k,v)

#endif // _CDICT_H_
