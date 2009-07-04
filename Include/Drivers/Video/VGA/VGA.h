/*
  *	File Name: /Drivers/Video/VGA/VGA.h
 *	Discription: Provides Driver functions for VGA Card
 *	Last Modified: 13 Jan' 2008
 */

#include "x86.h"
#include "mem.h"

#if !defined ( __VGA_H_ )
#define __VGA_H_

#define GRAPH_320x200x256		256
#define GRAPH_320x200x256_X		257

#define SUCCESS				0x0
#define MODE_NOT_SUPPORTED		0x1
#define VGA_ALREADY_INITIALIZED	0x2
#define VGA_NOT_INITIALIZED		0x3

extern unsigned char _320x200x256_grph[], _320x200x256_modex_grph[];

class VGA
{
 private:
     #define	VGA_AC_INDEX		0x3C0
     #define	VGA_AC_WRITE		0x3C0
     #define	VGA_AC_READ			0x3C1
     #define	VGA_MISC_WRITE		0x3C2
     #define	VGA_SEQ_INDEX		0x3C4
     #define	VGA_SEQ_DATA		0x3C5
     #define	VGA_DAC_READ_INDEX	0x3C7
     #define	VGA_DAC_WRITE_INDEX	0x3C8
     #define	VGA_DAC_DATA		0x3C9
     #define	VGA_MISC_READ		0x3CC
     #define	VGA_GC_INDEX 		0x3CE
     #define	VGA_GC_DATA 		0x3CF
     /*			COLOR emulation		MONO emulation */
     #define	VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
     #define	VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
     #define	VGA_INSTAT_READ		0x3DA

     #define	VGA_NUM_SEQ_REGS	5
     #define	VGA_NUM_CRTC_REGS	25
     #define	VGA_NUM_GC_REGS		9
     #define	VGA_NUM_AC_REGS		21
     #define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

     #define TICKS	    (*(volatile unsigned long *)(0x0040006CL))
     #define sgn(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a  number */

     char is_vga;
     unsigned int last_result;
     unsigned char * vid_mem;
     unsigned char off_screen[64000];
     unsigned int curr_x, curr_y, c_maxx, c_maxy;

     void write_regs(unsigned char *);
     unsigned long get_tick();
     void update_buffer();
 public:
     VGA();
     ~VGA();
     int init();
     int set_res(unsigned int);
     void clear(int col);
     void set_palette(int, unsigned char, unsigned char, unsigned char);
     void put_pixel(unsigned int, unsigned int, unsigned int);
     int get_pixel(int, int);
};

#endif
