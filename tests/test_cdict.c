#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <cutil/cdict.h>


void print_dictStat(cdict_t *d);
void printf_dict_value(cdict_t *d,char* key);
void test_addManyItems(cdict_t *d,const uint64_t count);
void test_addManyInts(cdict_t *d,const uint64_t count);


int main(const int argc,const char* argv[])
{
	cdict_t		*d=cdict_new();
	double*		tempDouble;

	(void)argc;
	(void)argv;
	printf("cdict record start.\n");
	printf("cdict record created.  %p\n",(void*)d);
	print_dictStat(d);
	test_addManyItems(d,10000);
	print_dictStat(d);

	cdict_set(d, "String", strdup("This is a test string."));
	cdict_set(d, "Fist", strdup("David"));
	cdict_set(d, "Last", strdup("Harris"));
	cdict_set(d, "State", strdup("Georgia"));
	cdict_set(d, "Int", strdup("52"));
	tempDouble=malloc(sizeof(double));
	*tempDouble=255.888;
	// cdict_set(d, "Double", tempDouble);
	cdict_set(d, "String2", strdup("This is a test string also."));
	print_dictStat(d);

	printf_dict_value(d,"String");
	printf_dict_value(d,"String2");
	printf_dict_value(d,"Int");
	printf_dict_value(d,"Int2");
	printf_dict_value(d,"Int3");
	printf_dict_value(d,"Int4");
	printf_dict_value(d,"Int5");
	printf_dict_value(d,"Int6");
	printf_dict_value(d,"30000");
	// tempDouble=cdict_get_vfork(d,"Double");
	// printf("cdict record '%s' -> %lf\n","Double",*tempDouble);
	// printf_dict_value(d,"TestDouble");
	fflush(stdout);
	print_dictStat(d);


	// printf("Dict(%p){State: %04X, Count: %lu\n",(void*)d,d->state,d->count);
	cdict_free(&d);
	printf("cdict record freed.\n");
	printf("d=%p.\n",(void*)d);
	return 0;
}

void print_dictStat(cdict_t *d)
{
	printf(" -[Dict]- (%p) {state: %d, Count: %lu, Alloc: %lu, flags: %d%d%d}\n",(void*)d,d->state,d->count,d->allocated,d->flags.add_if_unknown,d->flags.copy_keys,d->flags.free_val_on_set);
}

void test_addManyItems(cdict_t *d,const uint64_t count)
{
	char		key[32];
	char		value[40];

	memset(key,0,sizeof(key));
	memset(value,0,sizeof(value));
	for(uint64_t i=1;i<=count;i++)
	{
		sprintf(key,"%lu", i);
		sprintf(value,"Hello: 0x%06lX", i);
		cdict_set_dup(d, key, value,sizeof(value));
		if(i%1000==0)
		{
			printf(".");
			fflush(stdout);
		}
	}
	printf("\n");
}

void test_addManyInts(cdict_t *d,const uint64_t count)
{
	char		key[32];

	memset(key,0,sizeof(key));
	for(uint64_t i=1;i<=count;i++)
	{
		sprintf(key,"%lu", i);

		cdict_set_dup(d, key, &i,sizeof(i));
		if(i%1000==0)
		{
			printf(".");
			fflush(stdout);
		}
	}
	printf("\n");
}


void printf_dict_value(cdict_t *d,char* key)
{
	char	*tempVal=cdict_get_vfork(d,key);

	if(d->state==err_NOERROR)
		printf("cdict record '%s' -> %s\n",key,tempVal);
	else
		printf("***err*** can't find key: '%s'\n",key);
	cdict_reset(d);
}
