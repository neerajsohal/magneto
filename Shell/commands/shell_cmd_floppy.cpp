#include "Shell\Shell.h"
#include "cmos.h"

#if !defined ( __SHELL_CMD_CMOS_CPP_ )
#define __SHELL_CMD_CMOS_CPP_

void Shell::shell_cmd_floppy(void)
{
	cmos.disp_cmos_floppy();
}

#endif