#include "Drivers\Keyboard\Keyboard.h"

#if !defined ( __KB_BUF_CPP_ )
#define  __KB_BUF_CPP_ 

unsigned char KB_BUF[BUF_SIZE];

unsigned int front, rear;

void init_kb_buf()
{
 front = rear = -1;
}

unsigned is_full()
{
 if(((front == 0) && (rear == BUF_SIZE - 1))||(front == rear + 1)) return 1;
 else return 0;
}

unsigned is_empty()
{
 if((front == -1)) return 1;
 else return 0;
}

unsigned char kb_buf_insert(char ch)
{
 if(is_full()) return BUFFER_OVERFLOW;
 
 if(front == -1)
 {
  front = 0;
  rear = 0;
 }
 else if(rear == BUF_SIZE - 1) rear = 0;
      else rear = rear + 1;
 
 KB_BUF[rear] = ch;
}

unsigned char kb_buf_delete()
{
 if(is_empty()) return BUFFER_UNDERFLOW;
 
 unsigned char ch = KB_BUF[front];
 
 if(front == rear) rear = front = -1;
 else if(front = BUF_SIZE - 1) front = 0;
      else front = front + 1;
	  
 return ch;
}

#endif
