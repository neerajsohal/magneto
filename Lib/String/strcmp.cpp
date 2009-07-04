#include "string.h"

#if !defined ( __STRCMP_CPP_ )
#define __STRCMP_CPP_

int strcmp(char *dest, char *src )
{
	while ( *dest && *src && *dest == *src )
	{
		dest++;
		src++;
	}
	return *dest - *src;
}

#endif
