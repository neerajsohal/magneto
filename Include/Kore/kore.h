#include "Kore\kmsgs.h"

#if !defined ( __KORE_H_ )
#define __KORE_H_

extern const char * UNKNOWN_ID;
extern const char * KORE_ID;
void KORE_PANIC(const char *, const char *id = UNKNOWN_ID);

class Kore
{
 private:
	void print_debug_msg(int);
	void print_debug_success();
	void print_debug_faliure();
	void print_debug_fatalerr();
	const char * get_sig_msg(int);
	void halt_machine();
	void welcome(void);
 public:
    Kore();
    ~Kore();
    int init();
	void send_signal(int, const char *);
};

extern Kore kore;

#endif
