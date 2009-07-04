#include "mem.h"

#if !defined ( __MEMSET_CPP_ )
#define __MEMSET_CPP_

void *memsetw(void *dst, int val, unsigned long int count)
{
	unsigned short *temp = (unsigned short *)dst;

	for( ; count != 0; count--)
		*temp++ = val;
	return dst;
}

void *memsetb(void *dst, unsigned char val, unsigned long int count)
{
	unsigned char *temp = (unsigned char *)dst;

	for( ; count != 0; count--)
		*temp++ = val;
	return dst;
}

#endif
