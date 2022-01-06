/**
 * @file cprint_data.h
 */
#ifndef _CPRINT_H_
#define	_CPRINT_H_

#include <stdbool.h>
#include <stdint.h>


void cprint_bits8(uint8_t x);
void cprint_bits16(uint16_t x);
void cprint_bits32(uint32_t x);
void cprint_bits64(uint64_t x);


#endif // _CPRINT_H_
