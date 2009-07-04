#include "Drivers\Keyboard\Keyboard.h"

#if !defined ( __KB_IRQ_CPP_ )
#define  __KB_IRQ_CPP_ 


char normal[] = {
 0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
 'q','w','e','r','t','y','u','i','o','p','[',']',0x0D,0x80,
 'a','s','d','f','g','h','j','k','l',';',047,0140,0x80,
 0134,'z','x','c','v','b','n','m',',','.','/',0x80,
 '*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
 0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
 0x80,0x80,0x80,'0',0177 };

void keyboard_irq()
{
 SAVE_REGS;
 cli();

 unsigned char scancode, val;
 scancode = inportb(0x60);
 /* Read from the keyboard's data buffer */
 if(scancode & 0x80)
 {
  ;	//Shift CRTL ALT etc
 }
 else kb_buf_insert(normal[scancode]);

 sti();
 outportb(0x20,0x20);
 RESTORE_REGS;
 __asm__( "leave\n\t"
          "iret"     );
}


#endif
