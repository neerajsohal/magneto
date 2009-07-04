#include "Shell\Shell.h"
#include "kore\kdefs.h"

#if !defined ( __SHELL_CMD_VER_CPP_ )
#define __SHELL_CMD_VER_CPP_

void Shell::shell_cmd_ver(void)
{
	cout<<"\n"<<OEM_NAME<<" "<<"[version "<<MAJ_VER<<"."<<MIN_VER<<"]";
	cout<<"\nBuilt using gcc version 4.22, ld version 2.17 [DJGPP] and nasm 2.01rc1";
	cout<<"\nBuild Date: 29th Feb' 2008\n\n";
}

#endif
