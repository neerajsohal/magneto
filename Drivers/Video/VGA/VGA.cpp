/*
  *	File Name: /Drivers/Video/VGA/VGA.cpp
 *	Discription: Provides Driver functions for VGA Card
 *	Last Modified: 13 Jan' 2008
 */

#include "Drivers\Video\VGA\VGA.h"

#if !defined ( __VGA_CPP_ )
#define __VGA_CPP_

unsigned char _320x200x256_grph[] =
{
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00,	0x00
};

unsigned char _320x200x256_modex_grph[] =
{
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x06,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00, 0x00
};

VGA::VGA()
{
 vid_mem = (unsigned char *)0xA0000;
}

VGA::~VGA()
{
 ;
}

void VGA::write_regs(unsigned char *regs)
{
	unsigned i;

/* write MISCELLANEOUS reg */
	outportb(VGA_MISC_WRITE, *regs);
	regs++;
        outportb(VGA_INSTAT_READ, 0x00);
/* write SEQUENCER regs */
	for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		outportb(VGA_SEQ_INDEX, i);
		outportb(VGA_SEQ_DATA, *regs);
		regs++;
	}

/* unlock CRTC registers */
	outportb(VGA_CRTC_INDEX, 0x03);
	outportb(VGA_CRTC_DATA, inportb(VGA_CRTC_DATA) | 0x80);
	outportb(VGA_CRTC_INDEX, 0x11);
	outportb(VGA_CRTC_DATA, inportb(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;
/* write CRTC regs */
	for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		outportb(VGA_CRTC_INDEX, i);
		outportb(VGA_CRTC_DATA, *regs);
		regs++;
	}
/* write GRAPHICS CONTROLLER regs */
	for(i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		outportb(VGA_GC_INDEX, i);
		outportb(VGA_GC_DATA, *regs);
		regs++;
	}
/* write ATTRIBUTE CONTROLLER regs */
	for(i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)inportb(VGA_INSTAT_READ);
		outportb(VGA_AC_INDEX, i);
		outportb(VGA_AC_WRITE, *regs);
		regs++;
	}
/* lock 16-color palette and unblank display */
	(void)inportb(VGA_INSTAT_READ);
	outportb(VGA_AC_INDEX, 0x20);
}

unsigned long VGA::get_tick()
{
 return (unsigned long)(TICKS);
}

void VGA::update_buffer()
{
 while(inportb(VGA_INSTAT_READ) & 8);
 while(!(inportb(VGA_INSTAT_READ) & 8));

 memcpy(vid_mem, off_screen, c_maxx * c_maxy);
}

int VGA::init()
{
 if(is_vga == 1)
 {
  last_result = VGA_ALREADY_INITIALIZED;
 }
 else
 {
  set_res(GRAPH_320x200x256);
  is_vga = 1;
  last_result = SUCCESS;
 }
 return last_result;
}

int VGA::set_res(unsigned int mode)
{
 switch(mode)
 {
  case GRAPH_320x200x256: write_regs(_320x200x256_grph);
                          c_maxx = 319; c_maxy = 199;
                          last_result = SUCCESS;
	break;
  case GRAPH_320x200x256_X: write_regs(_320x200x256_modex_grph);
                          c_maxx = 319; c_maxy = 199;
                          last_result = SUCCESS;
	break;
  default: last_result = MODE_NOT_SUPPORTED;
	break;
  };
 clear(0);
 return last_result;
}

void VGA::clear(int col)
{
 memsetb(off_screen, col, c_maxx * c_maxy );
 update_buffer();
}

void VGA::set_palette (int color, unsigned char r, unsigned char g, unsigned char b)
{
 outportb (0x3C8, color);
 outportb (0x3C9, r);
 outportb (0x3C9, g);
 outportb (0x3C9, b);
}

void VGA::put_pixel(unsigned int x, unsigned int y, unsigned int col)
{
 off_screen[(y * c_maxx) + x] = col;
 update_buffer();
}

int VGA::get_pixel(int x, int y)
{
 return off_screen[(y * c_maxx) + x];
}

#endif
