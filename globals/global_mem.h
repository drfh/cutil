
#ifndef _GLOBAL_MEM_H_
#define	_GLOBAL_MEM_H_

//	Memmory management overide macros
#ifndef DHMALLOC
	#define	DHMALLOC(x)		malloc(x)
#endif
#ifndef DHFREE
	#define	DHFREE(x)		free(x)
#endif
#ifndef DHREALLOC
	#define	DHREALLOC(x,y)	realloc(x,y)
#endif

#endif // _GLOBAL_MEM_H_
