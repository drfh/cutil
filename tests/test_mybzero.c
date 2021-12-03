#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <cutil/mybzero.h>


void print_hex(void* p,int len)
{
	for(int i=0;i<len;i++)
		printf("%02X",(uint8_t)((uint8_t*)p)[i]);
}

int main()
{
	uint32_t	len=512;
	void*		p=malloc(len);

//	int		bytes=2;
//	int		shift=bytes*8;

	for(int i=0;i<32;i++)
		((uint8_t*)p)[i]=0x89;

	uint64_t	*ll64ptr=(uint64_t*)p;

	print_hex(ll64ptr,8);

	printf("\n");
	fflush(stdout);

	mybzero(p,4);

	printf("Test(%d): ",8);
	fflush(stdout);
	print_hex(ll64ptr,8);
	fflush(stdout);

	return 0;
}
