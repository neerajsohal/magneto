/*
 *  Module Name: Console
 *  File: Include\Console\Console.h
 *
 */

#include "x86.h"
#include "ctype.h"
#include "mem.h"
#include "defs.h"
#include "Drivers\Keyboard\Keyboard.h"
#include "iostream.h"

#include "Kore\kmsgs.h"


#if !defined ( __Console_H_ )
#define __Console_H_

#define TEXT_40x25	425
#define TEXT_40x50	450
#define TEXT_80x25	825
#define TEXT_80x50	850
#define TEXT_90x30	930
#define TEXT_90x60	960

#define MODE_NOT_SUPPORTED			0x1
#define CONSOLE_ALREADY_INITIALIZED	0x2
#define CONSOLE_NOT_INITIALIZED		0x3

#define COLOR_CARD	0x4
#define MONO_CARD	0x5
#define TAB			0x5

#if !defined(COLORS)
#define COLORS
 #define BLACK		0
 #define BLUE		1
 #define GREEN		2
 #define CYAN		3
 #define RED		4
 #define MAGENTA	5
 #define BROWN		6
 #define LIGHTGRAY	7
 #define DARKGRAY	8
 #define LIGHTBLUE	9
 #define LIGHTGREEN	10
 #define LIGHTCYAN	11
 #define PINK		12
 #define LIGHTMAGENTA	13
 #define YELLOW		14
 #define WHITE		15
#endif

#define BLINK   0x80 


#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ			0x3C1
#define	VGA_MISC_WRITE		0x3C2
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5
#define	VGA_DAC_READ_INDEX	0x3C7
#define	VGA_DAC_WRITE_INDEX	0x3C8
#define	VGA_DAC_DATA		0x3C9
#define	VGA_MISC_READ		0x3CC
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
/*			COLOR emulation		MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
#define	VGA_INSTAT_READ		0x3DA

#define	VGA_NUM_SEQ_REGS	5
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
				VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)


extern unsigned char _40x25_text[], _40x50_text[], _80x25_text[], _80x50_text[], _90x30_text[], _90x60_text[], g_8x8_font[2048], g_8x16_font[4096];
extern const char * CONSOLE_ID;

class Console
{
 private:
    static char is_console;
    static unsigned int last_result;
    static unsigned char * vid_mem;
    static unsigned int curr_x, curr_y, c_maxx, c_maxy, textattrib, fgcolor, bgcolor;

    int detect_card_type();
    void update_cursor();
    void scroll_line_up();
	void write_regs(unsigned char *);
	
 public:
    Console();
    ~Console();
    int init();
    int set_res(unsigned int);
    void settextbackground(int);
    void settextcolor(int);
    void settextattrib(int);
	int gettextcolor();
	int gettextbgcolor();
	int gettextattrib();
    int wherex();
    int wherey();
	int getmaxx();
	int getmaxy();
    void gotoxy(unsigned int, unsigned int);
    void clrscr();
    int writeln(const char *);
    void putch(const unsigned char);
    void writeint(const unsigned int);
    void writeint(const int);
};

extern Console console;

#endif
