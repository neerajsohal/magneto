#include "math.h"

#if !defined ( __MATH_CPP_ )
#define __MATH_CPP_

unsigned int abs(int val)
{
 if(val < 0) val = val * -1;
 return val;
}

unsigned long floor (unsigned long __x)
{
  register unsigned long __value;
  __volatile unsigned short int __cw, __cwtmp;

  __asm __volatile ("fnstcw %0" : "=m" (__cw));
  __cwtmp = (__cw & 0xf3ff) | 0x0400; /* rounding down */
  __asm __volatile ("fldcw %0" : : "m" (__cwtmp));
  __asm __volatile ("frndint" : "=t" (__value) : "0" (__x));
  __asm __volatile ("fldcw %0" : : "m" (__cw));

  return __value;
}

unsigned long ceil (unsigned long __x)
{
  register unsigned long __value;
  __volatile unsigned short int __cw, __cwtmp;

  __asm __volatile ("fnstcw %0" : "=m" (__cw));
  __cwtmp = (__cw & 0xf3ff) | 0x0800; /* rounding up */
  __asm __volatile ("fldcw %0" : : "m" (__cwtmp));
  __asm __volatile ("frndint" : "=t" (__value) : "0" (__x));
  __asm __volatile ("fldcw %0" : : "m" (__cw));

  return __value;
}

#endif
