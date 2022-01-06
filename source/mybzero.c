/**
 * @file mybzero.c
 */


#include <stdint.h>
#include <xmmintrin.h>


#if _WIN64 || __amd64__

void mybzero(void* p,const uint64_t len)
{
	uint64_t	*ptr=(uint64_t*)p;
	uint64_t	offset=0;

	while((((uint64_t)(void*)ptr) - (uint64_t)&p + 32) < len)
//	for(;(offset+32)<len;offset+=32)
	{
		ptr[0]=0x0000000000000000;
		ptr[1]=0x0000000000000000;
		ptr[2]=0x0000000000000000;
		ptr[3]=0x0000000000000000;
		*ptr+=32;
	}
	for(;(offset+8)<len;offset+=8)
	{
		*ptr=0x0000000000000000;
		ptr+=8;
	}
	uint64_t		bytes=len-offset;

	if(bytes)
	{
		uint64_t	mask=0xFFFFFFFFFFFFFFFF;
		uint64_t	shift=bytes*8;

		mask=mask>>shift;
		mask=mask<<shift;
		*ptr=*ptr&mask;
	}
}
#else

void mybzero(void* p,const uint32_t len)
{
	uint32_t	*ptr=(uint32_t*)p;
	uint32_t	offset=0;

	while((((uint32_t)(void*)ptr) - (uint32_t)&p + 16) < len)
//	for(;(offset+32)<len;offset+=32)
	{
		ptr[0]=0x00000000;
		ptr[1]=0x00000000;
		ptr[2]=0x00000000;
		ptr[3]=0x00000000;
		*ptr+=16;
	}
	for(;(offset+4)<len;offset+=4)
	{
		*ptr=0x00000000;
		ptr+=4;
	}
	uint32_t		bytes=len-offset;

	if(bytes)
	{
		uint32_t	mask=0xFFFFFFFF;
		uint32_t	shift=bytes*4;

		mask=mask>>shift;
		mask=mask<<shift;
		*ptr=*ptr&mask;
	}
}


#endif
