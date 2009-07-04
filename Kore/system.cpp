#include "Kore\System.h"

#if !defined ( __SYSTEM_CPP_ )
#define __SYSTEM_CPP_

magneto_system_t system_info;
System system;

System::System()
{
 system_info.system_name[0] = '\0';
 system_info.system_conv_mem = 0;
 system_info.system_ext_mem = 0;
}

System::~System()
{
 ;
}

int System::init(void)
{
 cout<<endl<<"SYSTEM:";
 cout<<"\n\tInitializing System Info";
 if(system_info.system_name[0] == '\0') return KMSG_FALIURE;
 else return KMSG_SUCCESS;
 
}

#endif
