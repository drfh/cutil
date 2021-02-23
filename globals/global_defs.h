#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>


#ifndef _GLOBAL_DEFS_H_
#define	_GLOBAL_DEFS_H_

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



#endif // _GLOBAL_DEFS_H_