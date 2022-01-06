/**
 * @file carray.h
 */
#ifndef _CARRAY_H_
#define	_CARRAY_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <assert.h>

/*!
 * \def kCARRAY_VERSION
 * \brief The version of the carray in ASCII c string format.
*/
#define	kCARRAY_VERSION					"1.0.0"

/**
 * \def kCARRAY_DEFAULT_PREALLOC
 * \brief How much of an array to preallocate by default.
 * Should be 32 unless edited.
 */
#define	kCARRAY_DEFAULT_PREALLOC		32

/**
 * @note	Experimental
 */
struct cbucket_t
{
	struct cbucket_t	*next;	/**< The next bucket in the linked list */
	struct cbucket_t	*prev;	/**< The previous bucket in the linked list  */
	void*		*ptr;			/**< Pointer to the allocated array */
	uint16_t	count;			/**< Number of elements in the is allocation */
};
typedef	struct cbucket_t	cbucket_t;


/**
 * @brief List of options for loading the global carray behaviour.
 * @note Using an enum declaration for no reason other that to finaly use it
 * @note Prabably would be a little faster with bitmask.
 * @note Might macro compile switch that later
 */
typedef	enum carr_opt{
	eShouldShrink,		/**< enum value eShouldShrink */
	eIsExperimental,	/**< enum value eIsExperimental */
	eSortAlgorithem,	/**< enum value eSortAlgorithem */
	eKeepSorted,		/**< enum value eKeepSorted */
	eCompareFunction	/**< enum value eCompareFunction */
}carrayopt_e;


typedef struct carray_flags_t
{
	bool	shouldShrink;
	bool	isExperimental;
	int		sortAlgorithem;
	int		(*compare)(const void*,const void*);
	int		keepSorted;
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
 * \param opt		Option that the value should be applied to
 * \param value		Value to set for the global defaults.
 * \see ca_opt carray_t
*/
void carray_init(carrayopt_e opt,const uintptr_t value);

/**
 * @brief Initializes the global carray behaviour with options
 * @retrun carray_t*	Newly allocated pointer.
*/
carray_t* carray_new(void);

/*! \fn carray_t* carray_new_allocsize(uint32_t size)
 * \brief Allocates a new carray_t with a preallocated array bucket size.
 * \param size The number of elements in the newly allocated array.
 */
carray_t* carray_new_allocsize(uint32_t size);

/**
 * @brief Set how big a chink should be allocated when the array tries to grow
 * @param a The array to make changes to.
 * @param increase The ammount of elements to allocate for.
 * @note The increase will only be a suggestion
 * @note The allocation will be the number of (elements * sizeof(void*))
 */
void carray_growHint(carray_t *a,uint32_t increase);

/**
 * @brief Create a new array from a C-syle array like main(argc,argv)
 * @param v the vector/array of pointers.
 * @param count The number of elements in the array.
 * @return An allocated carray_t pointing to the passed array without copying anything.
 * @see carray_add
 */
carray_t* carray_newfrom_vector(const void* v[],const int count);

/**
 * @brief Frees the memory alllocated by the array and sets the pointer to NULL before returning.
 * @note Warning the pointer that is passed will point to NULL if everything went correctly.
 * @note Function will remove each element of the array one at a time.
 * @see carray_destroy
 * @see carray_destroyClean
 */
void carray_free(carray_t **a);

/**
 * @brief Frees the memory alllocated by the array and sets the pointer to NULL before returning.
 * @note Warning the pointer that is passed will point to NULL if everything went correctly.
 * @note Function will attempt to free the pointer table without touching any of the elements. <br>
 * You may need to free the elements beforehand or after if you can.
 * @see carray_free
 * @see carray_destroyClean
 */
void carray_destroy(carray_t **a);

/**
 * @brief Add an element/item to the array.
 * @param a The array to make changes to.
 * @param p Ptr to the memory address to add the the array list.
 * @see carray_growHint
 */
void carray_add(carray_t *a,void* p);

/**
 * @brief Add an element/item to the array.
 * @param a The array to make changes to.
 * @param p Ptr to the memory address that will be added to the array list.
 * @note Pointe will be added to the very end of the array.
 */
void carray_addPtr(carray_t *a,void* ptr);
/**
 * @brief Insert an element/item to a specific index within the array.
 * @param a The array to make changes to.
 * @param p Ptr to the memory address to add the the array list.
 * @param index The index of the location within the array to place the new element.
 * @note The array will put the item at the very end if the index is over the table height.
 * @see carray_growHint
 */
void carray_insert(carray_t *a,void* ptr,uint64_t index);

void carray_remove(carray_t *a,void* ptr);
void carray_removeIndex(carray_t *a,uint64_t index);

void* carray_PtrAtindex(carray_t *a,uint64_t index);
uint64_t carray_IndexOfPtr(carray_t *a,void* ptr);

uint64_t carray_count(carray_t *a);
void carray_swap(carray_t *a,uint64_t index1,uint64_t index2);
void carray_MoveTo(carray_t *a,uint64_t from,uint64_t to);

void carray_sort(carray_t *arr,int (*compare)(const void*,const void*));
void carray_sort_selection(carray_t *a,int (*compare)(const void*,const void*));
void carray_sort_insertion(carray_t *arr,int (*compare)(const void*,const void*));

/**
 * \marco Marcro alias for the function carray_count(a)
 * @see carray_count
 */
#define carray_length(a)		carray_count(a)


/**
 * \fn Inline function to test if an array_t* is a NULL ptr.
 */
inline bool carray_IsNULL(carray_t *a)
{
	if(a==NULL)
		return true;
	return false;
}

/**
 * \fn Inline function to test if an array_t* is allocated but has no elements.
 */
inline bool carray_IsEmpty(carray_t *a)
{
	assert(!carray_IsNULL(a));
	if(a->count>0)
		return true;
	return false;
}


#endif // _CARRAY_H_
