/*
 *	Module Name: PC Speaker Driver
 *	File Name: /Drivers/Sound/PC_Speaker/PC_Speaker.cpp
 *	Discription: Driver for PC Speaker System
 *	Last Modified: 11 Jan' 2008
 */


#include "Drivers\Sound\PC_Speaker.h"

#if !defined ( __PC_SPEAKER_CPP_ )
#define __PC_SPEAKER_CPP_

PC_Speaker::PC_Speaker()
{
 ;
}

PC_Speaker::~PC_Speaker()
{
 ;
}

void PC_Speaker::init()
{
/* cout<<endl<<"PC Speaker:";
 sound(1500);
 nosound();
 cout<<"\n\t Initialized";*/
}

void PC_Speaker::sound(unsigned int frequency)
{
 unsigned char status;
 frequency = 1193182 / frequency;
	
 outportb(SPEAKER_CTRL , 0xB6);
 outportb(SPEAKER_DATA , (unsigned char)frequency);
 outportb(SPEAKER_DATA , (unsigned char)(frequency >> 0x08));

 status = inportb(0x61);
 if(status != (status|0x03)) outportb(0x61, status|3) ;
}

void PC_Speaker::nosound()
{
 outportb(0x61 , inportb(0x61) & 0xFC );
}

#endif
