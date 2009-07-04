#include "iostream.h"
#include "x86.h"
#include "kore\kmsgs.h"

#if !defined ( __CMOS_H_ )
#define __CMOS_H_

typedef struct cmos_s{
	unsigned char seconds;			/* 0x00*/			/* Seconds */
	unsigned char seconds_alarm;	/* 0x01*/			/* Seconds (alarm) */
	unsigned char minutes;			/* 0x02 */			/* Minutes */
	unsigned char minutes_alarm;	/* 0x03 */			/* Minutes (alarm) */
	unsigned char hours;			/* 0x04 */			/* Hours */
	unsigned char hours_alarm;		/* 0x05 */			/* Hours (alarm) */
	unsigned char day_of_week;		/* 0x06 */			/* Day of week */
	unsigned char day_of_month;		/* 0x07 */			/* Day of month */
	unsigned char month;			/* 0x08 */			/* Month */
	unsigned char year;				/* 0x09 */			/* Year */
	unsigned char a;				/* 0x0a*/			/* Status register A */
	unsigned char b;				/* 0x0b */			/* Status register B */
	unsigned char c;				/* 0x0c */			/* Status register C */
	unsigned char d;				/* 0x0d */			/* Status register D */
	unsigned char diagnosis;		/* 0x0e */			/* Diagnosis register */
	unsigned char shutdown;			/* 0x0f */			/* Shutdown status */
	unsigned char floppy;			/* 0x10 */			/* Floppy types */
	unsigned char reserved0;		/* 0x11 */			/* Reserved */
	unsigned char harddisk;			/* 0x12 */			/* Hard drive types */
	unsigned char reserved1;		/* 0x13 */			/* Reserved */
	unsigned char device;			/* 0x14 */			/* Device byte */
	unsigned int base_mem;			/* 0x15 - 0x16 */		/* Base memory */
	unsigned int ext_mem;			/* 0x17 - 0x18*/		/* Extended memory */
	unsigned char hdd1_ext;			/* 0x19 */			/* Extension for first HDD */
	unsigned char hdd2_ext;			/* 0x1a */			/* Extension for second HDD */
	unsigned char reserved2[5];		/* 0x1b - 0x1f */		/* Reserved */
	unsigned char hdd1_param[8];	/* 0x20 - 0x27 */ 		/* HDD one parameters */
	unsigned char reserved3[6];		/* 0x28 - 0x2d */		/* Reserved */
	unsigned int checksum;			/* 0x2e - 0x2f */		/* Checksum */
	unsigned int post_ext_mem;		/* 0x30 - 0x31 */		/* Post extended memory */
	unsigned char century;			/* 0x32 */			/* Century */
	unsigned int setup_info;		/* 0x33 - 0x34*/		/* Setup Information */
	unsigned char hdd2_param[8];	/* 0x35 */			/* HDD two parameters */
	unsigned char reserved4[3];		/* 0x3d - 0x3f */		/* Reserved */
}__attribute__((packed)) cmos_t;

typedef struct cmos_clock_s{
	unsigned int seconds;			/* 0x00*/			/* Seconds */
	unsigned int minutes;			/* 0x02 */			/* Minutes */
	unsigned int hours;			/* 0x04 */			/* Hours */
	unsigned int day_of_week;		/* 0x06 */			/* Day of week */
	unsigned int day_of_month;		/* 0x07 */			/* Day of month */
	unsigned int month;			/* 0x08 */			/* Month */
	unsigned int year;				/* 0x09 */			/* Year */
}__attribute__((packed)) cmos_clock_t;

extern cmos_t cmos_info; 
extern cmos_clock_t cmos_clock;
	
class CMOS
{
 private:
	#define CMOS_PORT 0x70
	#define CMOS_DATA 0x71

	#define RTC_SEC		0x00
	#define RTC_MIN		0x02
	#define RTC_HOUR	0x04
	#define RTC_DAYMON	0x07
	#define RTC_MONTH	0x08
	#define RTC_YEAR	0x09
	#define RTC_STATUS	11
	
	#define CMOS_BASEMEM1	0x15
	#define CMOS_BASEMEM2	0x16
	#define CMOS_EXTMEM1	0x17
	#define CMOS_EXTMEM2	0x18
	
	#define CMOS_FLOPPY		0x10
	
	unsigned int decode_rtc_data(unsigned char);
	unsigned char read_cmos();
	
	void send_cmos(unsigned char);
	void read_cmos_mem(void);
	void read_cmos_data(void);
	void read_cmos_clock(void);
	void read_cmos_floppy(void);
 public:
	CMOS();
	~CMOS();
	int init(void);
	void disp_cmos_info(void);
	void disp_cmos_date(void);
	void disp_cmos_time(void);
	void disp_cmos_floppy(void);
};

extern CMOS cmos;

#endif
