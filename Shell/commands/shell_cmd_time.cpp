#include "Shell\Shell.h"
#include "cmos.h"

#if !defined ( __SHELL_CMD_TIME_CPP_ )
#define __SHELL_CMD_TIME_CPP_

void Shell::shell_cmd_time(void)
{
	cmos.disp_cmos_time();
}

#endif
