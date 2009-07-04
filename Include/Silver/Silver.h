/*
 *	File Name: /Include/Silver/Silver.h
 *	Discription: Provides API For G-UI And Text-UI
 *	Last Modified: 01 Jan' 2008
 */

#if !defined ( __SILVER_H_ )
#define __SILVER_H_

#define	TUI	0;
#define GUI	1;

class Silver
{	
	public:
		Silver();
		~Silver();
		int init_mode(int TYPE, int MODE);
};

#endif
