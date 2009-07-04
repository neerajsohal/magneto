#include "Shell\Shell.h"

#if !defined ( __SHELL_CMD_HELP_CPP_ )
#define __SHELL_CMD_HELP_CPP_

void Shell::shell_cmd_help(void)
{
	cout<<"\nMagneto Help";
	cout<<"\nList of available commands";
	cout<<"\nhelp     -  Prints help information";
	cout<<"\nver      -  Prints version information";
	cout<<"\nlogout   -  Logs you out of the system";
	cout<<"\ndate     -  Displays current system date";
	cout<<"\ntime     -  Displays current system time";
	cout<<"\ncmos     -  Displays cmos Information";	
	cout<<"\nhalt     -  Halts the machine";
	cout<<"\nfloppy   -  Displays Floppy Information";
	cout<<"\nsystem   -  Displays System Information";
	cout<<"\nmem      -  Displays Memory Information";
	cout<<"\n\nAll commands are case-sensitive\n";
}

#endif
