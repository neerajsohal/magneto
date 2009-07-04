/*
 *	Module Name: PC Speaker Driver
 *	File Name: /Include/Drivers/Sound/PC_Speaker/PC_Speaker.h
 *	Discription: Driver for PC Speaker System
 *	Last Modified: 11 Jan' 2008
 */

#include "x86.h"
#include "defs.h"

#if !defined ( __PC_SPEAKER_H_ )
#define __PC_SPEAKER_H_

class PC_Speaker
{
 private:
    #define SPEAKER_CTRL	0x43
    #define SPEAKER_DATA	0x42
 public:
    PC_Speaker();
    ~PC_Speaker();
    void init();
    void beep();
    void sound(unsigned int);
    void nosound();
};

#endif
