#include "cmos.h"

#if !defined ( __CMOS_CPP_ )
#define __CMOS_CPP_

cmos_t cmos_info;
cmos_clock_t cmos_clock;

CMOS::CMOS()
{
 read_cmos_data();
}

CMOS::~CMOS()
{
 ;
}

int CMOS::init()
{
 cout<<endl<<"CMOS:";
 read_cmos_clock();
 cout<<"\n\tCurrent Date (dd-mm-yy): "<<(int)cmos_clock.day_of_month<<"-"<<(int)cmos_clock.month<<"-"<<(int)cmos_clock.year;
 return KMSG_SUCCESS;
}

unsigned int CMOS::decode_rtc_data(unsigned char data)
{
	unsigned int result;
	result = ((data >> 4) & 0x0F) * 10;
	result += (data & 0x0F);
	return result;
}

unsigned char CMOS::read_cmos()
{
 return inportb(CMOS_DATA);
}

void CMOS::send_cmos(unsigned char value)
{
 outportb(CMOS_PORT, value);
}

void CMOS::read_cmos_mem(void)
{
 send_cmos(CMOS_BASEMEM1);
 unsigned char base_mem_high = read_cmos();
 send_cmos(CMOS_BASEMEM2);
 unsigned char base_mem_low = read_cmos();
 send_cmos(CMOS_EXTMEM1);
 unsigned char ext_mem_high = read_cmos();
 send_cmos(CMOS_EXTMEM2);
 unsigned char ext_mem_low = read_cmos();
 
 cmos_info.base_mem = (base_mem_low | base_mem_high >> 8) * 1024L;
 cmos_info.ext_mem = (ext_mem_low | ext_mem_high >> 8) * 1024L;
}
void CMOS::read_cmos_clock(void)
{
 send_cmos(RTC_SEC);
 cmos_clock.seconds = decode_rtc_data(read_cmos());
 send_cmos(RTC_MIN);
 cmos_clock.minutes = decode_rtc_data(read_cmos());
 send_cmos(RTC_HOUR);
 cmos_clock.hours = decode_rtc_data(read_cmos());
 send_cmos(RTC_DAYMON);
 cmos_clock.day_of_month = decode_rtc_data(read_cmos());
 send_cmos(RTC_MONTH);
 cmos_clock.month = decode_rtc_data(read_cmos());
 send_cmos(RTC_YEAR);
 cmos_clock.year = decode_rtc_data(read_cmos());
}

void CMOS::read_cmos_floppy(void)
{
 send_cmos(CMOS_FLOPPY);
 cmos_info.floppy = (unsigned char) read_cmos();
}

void CMOS::read_cmos_data(void)
{
return;
 unsigned int val = 0x00;
 unsigned char * temp = (unsigned char *) &cmos_info;
 while(val != 0x3f)
 {
	outportb(0x70, 0x10);
	temp[val] = (unsigned char) inportb(0x71);
	val = val + 1;
	temp++;
 }
}

void CMOS::disp_cmos_info(void)
{
 read_cmos_data();
 read_cmos_mem();
 cout<<"\nCMOS Info:";
 cout<<"\nSeconds: ";
 cout<<(int)cmos_info.seconds;
 cout<<"\nSeconds alarm: ";
 cout<<(int)cmos_info.seconds_alarm;
  cout<<"\nMinutes: ";
 cout<<(int)cmos_info.minutes;
 cout<<"\nMinutes alarm: ";
 cout<<(int)cmos_info.minutes_alarm;
 cout<<"\nHours: ";
 cout<<(int)cmos_info.hours;
 cout<<"\nHours alarm: ";
 cout<<(int)cmos_info.hours_alarm;
 cout<<"\nDay of week: ";
 cout<<(int)cmos_info.day_of_week;
 cout<<"\nDay of month: ";
 cout<<(int)cmos_info.day_of_month;
 cout<<"\nMonth: ";
 cout<<(int)cmos_info.month;
 cout<<"\nYear: ";
 cout<<(int)cmos_info.year;
 cout<<"\nStatus Register a: ";
 cout<<cmos_info.a;
 cout<<"\nStatus Register b: ";
 cout<<cmos_info.b;
 cout<<"\nStatus Register c: ";
 cout<<cmos_info.c;
 cout<<"\nStatus Register d: ";
 cout<<cmos_info.d;
 cout<<"\nDiagnosis Register: ";
 cout<<cmos_info.diagnosis;
 cout<<"\nShutdown status: ";
 cout<<cmos_info.shutdown;
}

void CMOS::disp_cmos_date(void)
{
 read_cmos_clock();
 cout<<"\nCurrent Date (dd-mm-yy): "<<(int)cmos_clock.day_of_month<<"-"<<(int)cmos_clock.month<<"-"<<(int)cmos_clock.year;
 cout<<endl;
}

void CMOS::disp_cmos_time(void)
{
 read_cmos_clock();
 cout<<"\nCurrent Time (hh:mm:ss): "<<(int)cmos_clock.hours<<":"<<(int)cmos_clock.minutes<<":"<<(int)cmos_clock.seconds;
 cout<<endl;
}

void CMOS::disp_cmos_floppy(void)
{
 read_cmos_floppy();
 const char * drive_type[6] = { "No floppy drive", "360kb 5.25in floppy drive", "1.2mb 5.25in floppy drive", "720kb 3.5in", "1.44mb 3.5in", "2.88mb 3.5in"};
 cout<<"\nFloppy Types";
 cout<<"\nFloppy Drive A: ";
 cout<<drive_type[cmos_info.floppy >> 4];
 cout<<"\nFloppy Drive B: ";
 cout<<drive_type[cmos_info.floppy & 0xF];
 cout<<endl;
}

CMOS cmos;

#endif
