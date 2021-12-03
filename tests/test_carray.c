#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <assert.h>

#include <cutil/carray.h>


#define	kTEST_STR1		"This is a test string!"
#define	kTEST_STR2		"This is a test string, there are many like it but this one is ours!"

int test_carray_add4k(carray_t *a);
int test_carray_printStrings(carray_t *a);
int test_carray_strings(carray_t *a);
int test_carray_addInts(carray_t *a);
int test_carray_printInts(carray_t *a);



int main(const int argc,const char* argv[])
{
	carray_t*		a;

	(void)argc;
	(void)argv;

	carray_init(eShouldShrink,false);

	a=carray_new();
	assert(a!=NULL);
	test_carray_printStrings(a);
	assert(test_carray_add4k(a)==0);
	test_carray_printStrings(a);
	assert(test_carray_strings(a)==0);
	test_carray_printStrings(a);

	printf("Freeing array: %p\n",(void*)a);
	carray_free(&a);
	printf("Pointer should now be null: %p\n",(void*)a);

	a=carray_new();
	assert(test_carray_addInts(a)==0);
	test_carray_printInts(a);

	printf("\nDone.\n");
	return 0;
}

int test_carray_add4k(carray_t *a)
{
	char*			str;

	printf("Array length: %ld\n",carray_count(a));
	printf("Adding items to array: ");
	for(int i=0;i<1000*4;i++)
	{
		str=malloc(40);
		sprintf(str,"%s %d",kTEST_STR1,i);
		carray_add(a, str);
		printf(" %ld ",carray_count(a));
	}
	printf("\n");
	printf("Array length: %ld\n",carray_count(a));
	return 0;
}

int test_carray_printStrings(carray_t *a)
{
	char*			str;

	printf("\nPrinting the strings in the array: %p   %lu\n",(void*)a,carray_count(a));
	for(uint64_t i=0;i<carray_count(a);i++)
	{
		str=(char*)carray_PtrAtindex(a,i);
		printf("%p (%2X) -> %s\n",(void*)str,(int)i,str);
	}

	printf("\n");
	return 0;
}

int test_carray_printInts(carray_t *a)
{
	uint64_t		v;

	printf("\nPrinting the Ints in the array: %p   %lu\n",(void*)a,carray_count(a));
	for(uint64_t i=0;i<carray_count(a);i++)
	{
		v=(uint64_t)a->ptr[i];
		printf("%p (%2X) -> %lu\n",a->ptr[i],(int)i,v);
	}

	printf("\n");
	return 0;
}

int test_carray_strings(carray_t *a)
{
	printf("\n");
	printf("Doing the swapping test:\n");
	printf("Swap elements %d and %d\n",0,18);
	carray_swap(a,0,18);
	printf("Swap elements %d and %d\n",1,13);
	carray_swap(a,1,13);
	printf("Swap elements %d and %d\n",13,1);
	carray_swap(a,13,1);
	printf("Swap elements %d and %d\n",3,13);
	carray_swap(a,3,13);
	printf("Swap elements %d and %d\n",3,6);
	carray_swap(a,3,6);
	printf("Move element %d to %d\n",5,17);
	carray_MoveTo(a, 5, 17);
	printf("Move element %d to %d\n",4,17);
	carray_MoveTo(a, 4, 17);
	printf("Move element %d to %d\n",16,1);
	carray_MoveTo(a, 16, 1);
	printf("Move element %d to %d\n",16,1);
	carray_MoveTo(a, 16, 1);
	printf("Move element %d to %d\n",16,1);
	carray_MoveTo(a, 16, 1);
	// printf("Move element %d to %d\n",3,17);
	// carray_MoveTo(a, 3, 17);

	return (a==NULL);
}

int test_carray_addInts(carray_t *a)
{
//	char*			str;

	printf("Copy Ints to Array: %p\n",(void*)a);
	for(uint64_t i=0;i<1000*4;i++)
	{
		carray_add(a,(void*)i);
//		printf("%lu\n",i);
	}

	printf("->Done\n");
	return 0;
}
