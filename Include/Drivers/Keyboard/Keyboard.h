#include "x86.h"
#include "iostream.h"
#include "interrupts.h"
#include "kore\kmsgs.h"

#if !defined ( __KEYBOARD_H_ )
#define __KEYBOARD_H_

#define KB_PORT			0x60    /* keyboard port */
#define PORT_B          0x61
#define KB_CTRLR		0x64    /* keyboard controller port */
#define KBIT			0x80	/* bit used to ack characters to keyboard */

#define KB_SET_LEDS		0xED
#define KB_SET_TYPEMATIC_DELAY	0xF3

#define BUF_SIZE		255
#define BUFFER_OVERFLOW 0xFF
#define BUFFER_UNDERFLOW 0x00

extern unsigned char KB_BUF[BUF_SIZE];

void init_kb_buf();
unsigned is_full();
unsigned is_empty();
unsigned char kb_buf_insert(char);
unsigned char kb_buf_delete();
void keyboard_irq();

class Keyboard
{
 private:
    void update_leds(unsigned char);
    int busy();
    void reset_kb();
    void clear_hw_buf();
    void while_not_ready();
    void send_data(char);
 public:
    Keyboard();
    ~Keyboard();
    int init();
    void set_typematic_delay(unsigned char);
    char getch();
	char * getln();
};

extern Keyboard keyboard;

#endif
