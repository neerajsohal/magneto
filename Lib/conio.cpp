#include "conio.h"

#if !defined ( __CONIO_CPP_ )
#define __CONIO_CPP_

void gotoxy(int x, int y)
{
	console.gotoxy(x,y);
}

int wherex(void)
{
 return console.wherey();
}

int wherey(void)
{
 return console.wherey();
}

void textbackground(int color)
{
    console.settextbackground(color);
}

void textcolor(int color)
{
	console.settextcolor(color);
}

void textattrib(int color)
{
	console.settextattrib(color);
}

int gettextcolor()
{
	return console.gettextattrib();
}

int gettextattrib()
{
	return console.gettextattrib();
}

int getmaxx()
{
	return console.getmaxx();
}

int getmaxy()
{
	return console.getmaxy();
}

#endif
