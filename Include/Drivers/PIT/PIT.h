#include "x86.h"
#include "interrupts.h"
#include "iostream.h"
#include "kore\kmsgs.h"

#if !defined ( __PIT_H_ )
#define __PIT_H_

extern void PIT_irq();

class PIT
{
	private:
		void setup_timer(unsigned int);
	public:
		PIT();
		~PIT();
		int init(unsigned int);
};

extern PIT pit;

#endif
