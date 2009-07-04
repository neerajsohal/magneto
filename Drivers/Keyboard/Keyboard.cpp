#include "Drivers\Keyboard\Keyboard.h"

#if !defined ( __KEYBOARD_CPP_ )
#define  __KEYBOARD_CPP_ 

Keyboard::Keyboard()
{
 ;
}

Keyboard::~Keyboard()
{
 ;
}

int Keyboard::init()
{
 cout<<endl<<"Keyboard:";
 cout<<"\n\tEnabling Keyboard Interrupt. . .";
 interrupts.enable_irq(1, keyboard_irq, TRAP_GATE|BITS_32|PRESENT|RING_2);
 cout<<"\n\tResetting Keyboard . . .";
 reset_kb();
 init_kb_buf();
 return KMSG_SUCCESS;
}

void Keyboard::update_leds(unsigned char stat)
{
 while(busy());
 outportb(KB_PORT, KB_SET_LEDS);

 while(busy());
 outportb(KB_PORT, stat);
}

int Keyboard::busy()
{
 unsigned char temp = inportb(KB_CTRLR);
 
 if(temp & 0x2) return 1;
 else return 0;
}

void Keyboard::reset_kb()
{
 while(busy()) ;
 outportb(KB_PORT, 0xFF);
}

void Keyboard::clear_hw_buf()
{
 unsigned temp;
 do
 {
  temp = inportb(KB_CTRLR);
  if((temp & 0x01) != 0) 
  {
   (void)inportb(KB_PORT);
   continue;
  }
 } while((temp & 0x02) != 0);
}

void Keyboard::while_not_ready()
{
 volatile long i = 10;
 while (i-- && (inportb(KB_CTRLR) & 0x02));
}

void Keyboard::set_typematic_delay(unsigned char rate)
{
 while_not_ready();
 outportb(KB_PORT, KB_SET_TYPEMATIC_DELAY);
 outportb(KB_PORT, rate);
}

char Keyboard::getch()
{
 char ch = kb_buf_delete();
 if(ch == BUFFER_UNDERFLOW) return BUFFER_UNDERFLOW;
 else return ch;
}

Keyboard keyboard;

#endif
