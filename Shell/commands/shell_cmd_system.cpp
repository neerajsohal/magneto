#include "Shell\Shell.h"
#include "kore\system.h"

#if !defined ( __SHELL_CMD_SYSTEM_CPP_ )
#define __SHELL_CMD_SYSTEM_CPP_

void Shell::shell_cmd_system(void)
{
	cout<<"\n";
	cout<<"Lower Memory: "<<(int)system_info.system_conv_mem<<" KB";
	cout<<"\nUpper Memory: "<<(int)system_info.system_ext_mem<<" KB";
	cout<<endl;
}

#endif
