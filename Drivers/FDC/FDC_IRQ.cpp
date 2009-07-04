#include "Drivers\FDC\fdc.h"

void FDC_irq()
{
 SAVE_REGS;
 sti();
 done = 1;
 cli();
 outportb(0x20,0x20);
 RESTORE_REGS;
 __asm__( "leave\n\t"
          "iret"     );
}

/* This is the timer (int 1ch) handler */
void INT_1C(void)
{
   if (tmout) --tmout;     /* bump timeout */
   
   if (mtick > 0)
     --mtick;
   else if (!mtick && motor) {
      outportb(FDC_DOR,0x0c);  /* turn off floppy motor */
      motor = FALSE;
   }
}
