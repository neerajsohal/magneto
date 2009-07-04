#include "Shell\Shell.h"
#include "kore\kore.h"
#include "kore\kmsgs.h"

#if !defined ( __SHELL_CMD_HALT_CPP_ )
#define __SHELL_CMD_HALT_CPP_

void Shell::shell_cmd_halt(void)
{
	kore.send_signal(KSIG_HALT_MACHINE, SHELL_ID);
}

#endif
