#include "Drivers\Video\Console\Console.h"

#if !defined ( __CONIO_H_ )
#define __CONIO_H_

void gotoxy(int, int);
void textbackground(int color);
void textcolor(int color);
void textattrib(int color);
int gettextcolor();
int gettextattrib();
int wherex();
int wherey();
int getmaxx();
int getmaxy();

#endif
