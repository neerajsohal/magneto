#include "Drivers\PIT\PIT.h"
#include "Drivers\FDC\FDC.h"

#if !defined ( __PIT_IRQ_CPP_ )
#define  __PIT_IRQ_CPP_ 

unsigned int tick;

void FDC_1C()
{
  if (tmout) --tmout;     /* bump timeout */
   
   if (mtick > 0)
     --mtick;
   else if (!mtick && motor) {
      outportb(FDC_DOR,0x0c);  /* turn off floppy motor */
      motor = FALSE;
   }
}

void PIT_irq()
{
 SAVE_REGS;
 cli();
  FDC_1C();
 sti();
 outportb(0x20,0x20);
 RESTORE_REGS;
 __asm__( "leave\n\t"
          "iret"     );
}

#endif
