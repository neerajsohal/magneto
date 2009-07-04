#include "kore\kmsgs.h"
#include "iostream.h"

#if !defined ( __SYSTEM_H_ )
#define __SYSTEM_H_

struct magneto_system_t
{
 unsigned char system_name[25];
 unsigned int system_conv_mem;
 unsigned long system_ext_mem;
};

extern magneto_system_t system_info;

class System
{
 private:
 public:
	System();
	~System();
	int init(void);
};

extern System system;


#endif
