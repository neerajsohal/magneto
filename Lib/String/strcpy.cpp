#include "string.h"

#if !defined ( __STRCPY_CPP_ )
#define __STRCPY_CPP_

int strcpy(char * dest, char *src)
{
	char *d = dest;
	char *s = src;
	int count;
	while (*s)
	{
		*(d++) = *(s++);
		count++;
	}
	*(d++) = '\0';	// Null terminate
	return count;
}


#endif
