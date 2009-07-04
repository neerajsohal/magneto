/*
  *	File Name: /Kore/Kore.cpp
 *	Discription: Main Kernel File. Sets Up Environment For The OS
 *	Last Modified: 01 Jan' 2008
 */

#include "defs.h"
#include "kore\kdefs.h"
#include "x86.h"
#include "GDT.h"
#include "iostream.h"
#include "interrupts.h"
#include "Drivers\PIT\PIT.h"
#include "Drivers\Keyboard\Keyboard.h"
#include "Drivers\Video\VGA\VGA.h"
#include "Drivers\FAT\FAT.h"
#include "Drivers\FDC\FDC.h"
#include "Shell\shell.h"
#include "multiboot.h"
#include "cpuid.h"
#include "cmos.h"
#include "conio.h"
#include "kore\delay.h"
#include "kore\system.h"

#include "Kore\kore.h"

#if !defined ( __KORE_CPP_ )
#define __KORE_CPP_

const char * UNKNOWN_ID = "Unkown ID";
const char * KORE_ID = "KORE";

VGA vga;
Kore kore;

Kore::Kore()
{
 ;
}

Kore::~Kore()
{
 ;
}

void Kore::print_debug_success()
{
	int tx,ty;
	tx = wherex();
	ty = wherey();
	gotoxy(getmaxx() - 25, ty);
	int temp = gettextattrib();
	cout<<"\t[";
	textattrib(GREEN);
	cout<<"SUCCESS";
	textattrib(temp);
	cout<<"]";
}

void Kore::print_debug_faliure()
{
	int tx,ty;
	tx = wherex();
	ty = wherey();
	gotoxy(getmaxx() - 25, ty);
	int temp = gettextattrib();
	cout<<"\t[";
	textattrib(BROWN);
	cout<<"FAILED";
	textattrib(temp);
	cout<<"]";
}

void Kore::print_debug_fatalerr()
{
	int tx,ty;
	tx = wherex();
	ty = wherey();
	gotoxy(getmaxx() - 25, ty);
	int temp = gettextattrib();
	cout<<"\t[";
	textattrib(RED);
	cout<<" FATAL ";
	textattrib(temp);
	cout<<"]";
	send_signal(KSIG_HALT_MACHINE, KORE_ID);
}
const char * Kore::get_sig_msg(int SIGNAL)
{
	switch(SIGNAL)
	{
		case 0xff: return "KSIG_HALT_MACINE";
			break;
		default: return "KSIG_UNKOWN";
	};
}

void Kore::halt_machine()
{
	cout<<"\nMachine Halted";
	cli();
	hlt();
	while(1);
}

void Kore::print_debug_msg(int KMSG)
{
	switch(KMSG)
	{
		case KMSG_SUCCESS: print_debug_success();
			break;
		case KMSG_FALIURE: print_debug_faliure();
			break;
		case KMSG_FATAL_ERROR: print_debug_fatalerr();
			break;
	};
}

void Kore::welcome(void)
{
 int color = gettextcolor();
 textcolor(GREEN);
 cout<<"\n\nWelcome to "<<OEM_NAME<<" version "<<MAJ_VER<<"."<<MIN_VER;
 textcolor(color);
}

int Kore::init()
{
 print_debug_msg(console.init());
 print_debug_msg(gdt.init());
 print_debug_msg(interrupts.init());
 print_debug_msg(cpu.init());
 print_debug_msg(keyboard.init());
 print_debug_msg(delay.init());
 print_debug_msg(pit.init(100));
 print_debug_msg(fdc.init());
 print_debug_msg(cmos.init());
 print_debug_msg(fat.init());
 system_info.system_conv_mem = mbi_global->mem_lower;
 system_info.system_ext_mem = mbi_global->mem_upper;
 print_debug_msg(system.init());
 welcome();
 cout<<endl<<"Passing Control To Shell . . .";
 shell.init();
}

void Kore::send_signal(int SIGNAL, const char *id = UNKNOWN_ID)
{
	cout<<"\nKORE: ";
	switch(SIGNAL)
	{
		case KSIG_HALT_MACHINE:
			int temp = gettextattrib();
			textattrib(RED);
			cout<<"Recieved Signal: "<<get_sig_msg(SIGNAL);
			cout<<"\nSignal Sender ID: "<<id;
			halt_machine();
			break;
	};
}

int main(unsigned int magic, multiboot_info_t *mbi)
{
 /* Save the pointer into global multiboot structures */
 magic_global=magic;
 mbi_global=mbi;
 /*print_multiboot_info(magic, mbi);*/
 kore.init();
 return 0;
}

void KORE_PANIC(const char * msg, const char *id)
{
	cout<<"\nKore Panic";	//Bug not getting displayed
	kore.send_signal(KSIG_HALT_MACHINE, id);
}

#endif
