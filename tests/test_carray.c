/**
 * @Author: david
 * @Date:   2021-12-03T19:14:15-05:00
 * @Last modified by:   david
 * @Last modified time: 2021-12-31T18:29:23-05:00
 */


 #include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <cutil/carray.h>


#define	kTEST_STR1		"This is a test string!"
#define	kTEST_STR2		"This is a test string, there are many like it but this one is ours!"

int test_carray_addNumStr(carray_t *a,uint32_t num);
int test_carray_addNumStrRandom(carray_t *a,uint32_t num);
int test_carray_printStrings(carray_t *a);
int test_carray_strings(carray_t *a);
int test_carray_addInts(carray_t *a);
int test_carray_printInts(carray_t *a);

int mycompare(const void* a,const void* b);

int mycompare(const void* a,const void* b)
{
	return strcmp((char*)a,(char*)b);
	// return 0;
}


int main(const int argc,const char* argv[])
{
	carray_t*		a;
	carray_t*		args;

	bool	ShouldShrink=false;
	carray_init(eShouldShrink,ShouldShrink);
	carray_init(eSortAlgorithem,0);
	carray_init(eCompareFunction,(uintptr_t)&mycompare);
	carray_init(eKeepSorted,1);
	srand(time(NULL));

	args=carray_newfrom_vector((void*)argv,argc);
	printf("--------------\n");
	printf("Printing: main() args\n");
	test_carray_printStrings(args);
	printf("--------------\n");
	carray_removeIndex(args,0);
	test_carray_printStrings(args);
	printf("--------------\n");
	carray_sort(args,NULL);
	test_carray_printStrings(args);
	printf("--------------\n");

	a=carray_new();
	assert(a!=NULL);
	// test_carray_printStrings(a);
	// assert(test_carray_addNumStr(a,40)==0);
	assert(test_carray_addNumStrRandom(a,40)==0);
	// assert(test_carray_add4kRandom(a)==0);
	// assert(test_carray_add4kRandom(a)==0);
	// assert(test_carray_add4kRandom(a)==0);
	// test_carray_printStrings(a);
	// assert(test_carray_strings(a)==0);
	// test_carray_printStrings(a);
	// test_carray_printStrings(a);
//	carray_MoveTo(a,0,1);
//	test_carray_printStrings(a);

	// test_carray_printStrings(a);
	// carray_sort_selection(a,mycompare);
	carray_sort(a,NULL);
	test_carray_printStrings(a);

	printf("Freeing array: %p\n",(void*)a);
	carray_free(&a);
	printf("Pointer should now be null: %p\n",(void*)a);
	return 0;

	a=carray_new();
	assert(test_carray_addInts(a)==0);
	test_carray_printInts(a);

	printf("\nDone.\n");
	return 0;
}

int test_carray_addNumStr(carray_t *a,uint32_t num)
{
	char*			str;

	// printf("Adding items to array: ");
	for(uint32_t i=1;i<num;i++)
	{
		str=malloc(40);
		sprintf(str,"%s %05d",kTEST_STR1,i);
		carray_add(a, str);
		// printf(" %ld ",carray_count(a));
	}
	// printf("\n");
	printf("Array length: %ld\n",carray_count(a));
	return 0;
}

int test_carray_addNumStrRandom(carray_t *a,uint32_t num)
{
	char*			str;

	// printf("Adding items to array: ");
	for(uint32_t i=0;i<num;i++)
	{
		str=malloc(40);
		sprintf(str,"%s %05d",kTEST_STR1,rand()%100000);
		carray_add(a, str);
		// printf(" %ld ",carray_count(a));
	}
	// printf("\n");
	printf("Array length: %ld\n",carray_count(a));
	return 0;
}

int test_carray_printStrings(carray_t *a)
{
	char*			str;

	printf("Printing the strings in the array: %p   %lu\n",(void*)a,carray_count(a));
	for(uint64_t i=0;i<carray_count(a);i++)
	{
		str=(char*)carray_PtrAtindex(a,i);
		printf("%p (%2X) -> %s\n",(void*)str,(int)i,str);
	}
	return 0;
}

int test_carray_printInts(carray_t *a)
{
	uint64_t		v;

	printf("Printing the Ints in the array: %p   %lu\n",(void*)a,carray_count(a));
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
