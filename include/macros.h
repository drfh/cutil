/**
 * @Author: david
 * @Date:   2021-12-03T19:14:15-05:00
 * @Last modified by:   david
 * @Last modified time: 2021-12-26T08:27:07-05:00
 */



#ifndef _CUTIN_MACROS_H_
#define	_CUTIN_MACROS_H_

#include "ANSI-color-codes.h"

#define	__UNUSED__(x)		((void)x)
#define	__POINTER(x)		((void*)x)
#define	__HANDLE(x)			((void**)x)


//	Memmory allocation size macros
#define kKB(x)		(x*1024)
#define kMB(x)		(x*kKB(1000))
#define kGB(x)		(x*kMB(1000))
#define kTB(x)		(x*kGB(1000))
#define kPB(x)		(x*kTB(1000))

//	Not right but place holder
#define kKb(x)		(x*1000)
#define kMb(x)		(x*kKb(1000))
#define kGb(x)		(x*kMb(1000))
#define kTb(x)		(x*kGb(1000))
#define kPb(x)		(x*kTb(1000))

#define kKB4		(kKB(4))
#define k4KB		(kKB(4))

extern int make_iso_compilers_happy;



#define COLD __attribute__((cold))
#define UNUSED __attribute__((unused))
#define EXPORT __attribute__((visibility("default")))



#endif // _CUTIN_MACROS_H_
