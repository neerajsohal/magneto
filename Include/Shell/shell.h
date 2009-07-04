#include "defs.h"
#include "iostream.h"
#include "string.h"
#include "Kore\kore.h"
#include "shell\shell_cmds.h"

#if !defined ( __SHELL_H_ )
#define __SHELL_H_

extern const char * SHELL_ID;

class Shell
{
	private:
		unsigned char IS_LOGGEDIN;
		char name[21];
		char shell_buffer[128];
		void greet(void);
		void prompt(void);
		int login(void);
		int logout(void);
		
		
		/* Shell Internal commands */
		void parse_input(void);
		void shell_cmd_help(void);
		void shell_cmd_ver(void);
		void shell_cmd_logout(void);
		void shell_cmd_date(void);
		void shell_cmd_time(void);
		void shell_cmd_cmos(void);
		void shell_cmd_floppy(void);
		void shell_cmd_halt(void);
		void shell_cmd_system(void);
	public:
		Shell();
		~Shell();
		void init(void);

};

extern Shell shell;

#endif
