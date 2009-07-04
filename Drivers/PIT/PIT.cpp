#include "Drivers\PIT\PIT.h"

#if !defined ( __PIT_CPP_ )
#define __PIT_CPP_

PIT::PIT()
{
 ;
}

PIT::~PIT()
{
 ;
}

int PIT::init(unsigned int freq)
{
 cout<<endl<<"PIT:";
 cout<<"\n\tInitiazing PIC . . .";
 interrupts.enable_irq(0, PIT_irq, TRAP_GATE|BITS_32|PRESENT|RING_2);
 setup_timer(freq);
 cout<<"\n\tTimer Interval: "<<freq<<"Hz";
 return KMSG_SUCCESS;
}

void PIT::setup_timer(unsigned int frequency)
{
   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   unsigned int divisor = 1193180 / frequency;

   // Send the command byte.
   outportb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   unsigned char l = (unsigned char)(divisor & 0xFF);
   unsigned char h = (unsigned char)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outportb(0x40, l);
   outportb(0x40, h);
}

PIT pit;

#endif
