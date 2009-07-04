#include "string.h"

#if !defined ( __STRLEN_CPP_ )
#define __STRLEN_CPP_

unsigned int strlen(const char *str)
{
	unsigned int ret_val;

	for(ret_val = 0; *str != '\0'; str++)
		ret_val++;
	return ret_val;
}

#endif
