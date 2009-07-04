/*
 *	Module Name: x86 Dependent Funtions
 *	File Name: /Arch/x86.cpp
 *	Discription: Implements various x86 dependent Functions
 *	Last Modified: 07 Jan' 2008
 */
 
#include "x86.h"

#if !defined ( __X86_CPP_ )
#define __X86_CPP_

unsigned inportb(unsigned port)
{
	unsigned val;

	__asm__ __volatile__("inb %w1,%b0"
		: "=a"(val)
		: "d"(port));
	return val;
}


void outportb(unsigned port, unsigned val)
{
	__asm__ __volatile__("outb %b0,%w1"
		:
		: "a"(val), "d"(port));
}

unsigned int inportw(unsigned int port)
{

    unsigned int val;
    asm volatile("movw %1, %%dx;\
                 in %%dx, %%ax;\
                 movw %%ax, %0"
                :"=m"(val)
                :"m"(port)
                :"%eax","%edx");
    return val;
}


void outportw(unsigned int port, unsigned int val)
{
    asm volatile("movw %0, %%dx;\
                  movw %1, %%ax;\
                  out %%ax, %%dx;"
                : 
                :"m"(port),"m"(val)
                :"%eax","%edx");
}


void sti()
{
	__asm__ __volatile__( "sti" );	
}


void cli()
{
	__asm__ __volatile__( "cli" );	
}

void hlt()
{
	__asm__ __volatile__( "hlt" );	
}


int reboot()
{
 cli();
 int temp;		// A temporary int for storing keyboard info. The keyboard can be use to  reboot the PC

 // Get ready for reboot...flush the keyboard controller
 do
 {
  temp = inportb( 0x64 );
  if ( temp & 1 ) inportb( 0x60 );
 } while ( temp & 2 );

 // Reboot the computer...
 outportb(0x64, 0xFE);

 return -1;
}

#endif
