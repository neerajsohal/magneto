#include "iostream.h"
#include "kore\kmsgs.h"

#if !defined ( __CPUID_H_ )
#define __CPUID_H_

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

class CPU
{
 private:
	void cpuid_vendor(void);
	void cpuid_psn(void);
	void cpuid_features(void);
	void cpuid_intel(void);
	void printregs(int, int, int, int);
 public:
	CPU();
	~CPU();
	int init(void);
	void cpuid_detect(void);
};

extern CPU cpu;
#endif
