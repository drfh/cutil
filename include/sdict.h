#include <stdint.h>
#include <stdbool.h>

#ifndef _SDICT_H_
#define	_SDICT_H_

#include "cdict.h"

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


typedef	struct
{
	value_t			kv;
	// sdict_t		d;
}sdict_t;


/**
 * Initilization of the sdict background settings like flags that should be used when allocating and setting.
 *
 * @see sdict.h
 */
void sdict_init(void);

/**
 * A brief description. A more elaborate class description
 * @see sdict_t
 * @return A pointer to a sdict_t struct.
 */
sdict_t* sdict_new(void);

/**
 * Create a sdict_t* pointer with a preallocated array for key/values.
 * This is important for large dictionaries so that they don't need reallocations while adding keys.
 * @param size an integer of how many records to preallocate.
 * @see sdict_t
 * @see sdict_new()
 * @return A pointer to a sdict_t struct.
*/
sdict_t* sdict_new_allocsize(uint32_t size);
//void sdict_growHint(sdict_t *d,uint32_t increase);

/**
 * Gets the number of key/value pairs referanced in the dictionary parameter d
 * @param d The pointer to the dictionary record sdict_t
 * @see sdict_t
 * @see sdict_new()
 * @return size of the array holding the key/value elements.
*/
int sdict_size(sdict_t *d);

/**
 * a normal member taking two arguments and returning an integer value.
 * @param d The handle to the dictionary record sdict_t** that will be freed and set to NULL
 * @see sdict_t
*/
void sdict_free(sdict_t **dict);
void sdict_destroy(sdict_t **d);

//void sdict_add(sdict_t *d,char* key,void* ptr,type_t t);
//void sdict_add(sdict_t *d,char* key,void* ptr);
//void sdict_add_kv(sdict_t *d,keyval_t *kv);

void sdict_remove(sdict_t *d,char* key);

void* sdict_get_vfork(sdict_t *d,char* key);
#define	sdict_get_value_for_keyk(d,k)	sdict_set_vfork(d,k)
#define	sdict_get(d,k)					sdict_set_vfork(d,k)

//void* sdict_set_vfork_o(sdict_t *d,char* key,void* v,bool copy);
void* sdict_set_vfork(sdict_t *d,char* key,void* v);
#define	sdict_set_value_for_key(d,k,v)	sdict_set_vfork(d,k,v)
#define	sdict_set(d,k,v)				sdict_set_vfork(d,k,v)
//void sdict_set_vfork(sdict_t *d,char* key,void* v,type_t t);

#endif // _sdict_H_
