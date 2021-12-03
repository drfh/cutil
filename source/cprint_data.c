#include "cprint_data.h"

#include <stdlib.h>
#include <stdio.h>



const char *bit_rep[16] = {
	[ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
	[ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
	[ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
	[12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};


void cprint_bits8(uint8_t x)
{
	printf("%s%s",bit_rep[(x>>4)&0xf],bit_rep[x&0xf]);
}

void cprint_bits16(uint16_t x)
{
	printf("%s%s%s%s",bit_rep[(x>>12)&0xf],bit_rep[(x>>8)&0xf],bit_rep[(x>>4)&0xf],bit_rep[x&0xf]);
}

void cprint_bits32(uint32_t x)
{
	cprint_bits16(x>>16);
	cprint_bits16(x);
}

void cprint_bits64(uint64_t x)
{
	cprint_bits32(x);
	cprint_bits32(x>>32);
}
