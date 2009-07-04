#include "Shell\Shell.h"
#include "cmos.h"

#if !defined ( __SHELL_CMD_DATE_CPP_ )
#define __SHELL_CMD_DATE_CPP_

void Shell::shell_cmd_date(void)
{
	cmos.disp_cmos_date();
}

#endif
