#include "drivers\FAT\FAT.h"

#if !defined ( __FAT_CPP_ )
#define __FAT_CPP_

const char * FAT_ID = "FAT";

FAT::FAT()
{
 ;
}

FAT::~FAT()
{
 ;
}

int FAT::init()
{
 cout<<endl;
 cout<<"FAT: ";
 cout<<"\n\tNot Implemented";
 fdc.read_block(0, (unsigned char *)fat12_boot_info);
 return KMSG_FALIURE;
}

FAT fat;

#endif
