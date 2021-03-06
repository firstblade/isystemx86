/**
	@File:			stdio.h
	@Author:		Ihsoh
	@Date:			2014-1-19
	@Description:
*/

#ifndef	_ILIB_STDLIB_H_
#define	_ILIB_STDLIB_H_

#include "stdlib/stdlib.h"

#include "types.h"

extern void * malloc(uint num_bytes);
extern void * calloc(uint n, uint size);
extern void free(void * ptr);
extern void * realloc(void * mem_address, uint newsize);
extern void * realloc(void * mem_address, unsigned int newsize);
extern void exit(int status);

extern void qsort(void *base, int num, int size, int (*comparator)(const void *, const void *));


extern unsigned long int strtoul(const char * nptr, char ** endptr, int base);
extern long int strtol(const char * nptr, char ** endptr, int base);
extern double strtod(const char * nptr, char ** endptr);

#endif
