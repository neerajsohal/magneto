#include "Shell\Shell.h"

#if !defined ( __SHELL_CMD_LOGOUT_CPP_ )
#define __SHELL_CMD_LOGOUT_CPP_

void Shell::shell_cmd_logout(void)
{
	cout<<"\nLogging you out of the system . . .";
	if(!logout())
	{
		KORE_PANIC("Logout Error");
	}
	else cout<<"\tSuccessfull\n";
}

#endif
