#include "Shell\Shell.h"

#if !defined ( __SHELL_CPP_ )
#define __SHELL_CPP_

Shell shell;
const char * SHELL_ID = "SHELL";

char SHELL_PROMPT[15] = "@magneto$ ";

Shell::Shell()
{
 IS_LOGGEDIN = 0;
  //strcpy(SHELL_PROMPT, (char *)"@magneto\\>");
}

Shell::~Shell()
{
 ;
}

void Shell::greet()
{
 login();
 prompt();
}

int Shell::login(void)
{
 if(IS_LOGGEDIN) return 0;
 
 int done = 0;
 cout<<endl;
 while(!done)
 {
  cout<<"Login: ";
  cin>>name;
  if(name[0] == '\0') done = 0;
  else done = 1;
 }
 cout<<"\nThank you for logging in "<<name<<". Have a Nice Time.";
 cout<<"\nType 'help' for help\n";
 return 1;
}

void Shell::prompt()
{
 cout<<endl;
 while(TRUE)
 {
	cout<<name<<SHELL_PROMPT;
	cin>>shell_buffer;
	parse_input();
 }
}

void Shell::parse_input()
{
	if(shell_buffer[0] == '\0') return;
	else if(strcmp(shell_buffer, "ver") == 0)
	{
		shell_cmd_ver();
	} else if(strcmp(shell_buffer, "help") == 0)
	{
		shell_cmd_help();
	} else if(strcmp(shell_buffer, "logout") == 0)
	{
		shell_cmd_logout();
		login();		
	} else if(strcmp(shell_buffer, "date") == 0)
	{
		shell_cmd_date();
	} else if(strcmp(shell_buffer, "time") == 0)
	{
		shell_cmd_time();
	} else if(strcmp(shell_buffer, "floppy") == 0)
	{
		shell_cmd_floppy();
	} else if(strcmp(shell_buffer, "cmos") == 0)
	{
		shell_cmd_cmos();
	} else if(strcmp(shell_buffer, "halt") == 0)
	{
		shell_cmd_halt();
	}  else if(strcmp(shell_buffer, "system") == 0)
	{
		shell_cmd_system();
	} else cout<<"Shell: Unknown command\n";
}

int Shell::logout(void)
{
 return 1;
}

void Shell::init()
{
 greet();
}

#endif
