#include "cpuid.h"

#if !defined ( __CPUID_CPP_ )
#define __CPUID_CPP_


const char *Intel[] = {
	"Brand ID Not Supported.", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor"
};

const char *Intel_Other[] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved"
};



CPU::CPU()
{
 ;
}

CPU::~CPU()
{
 ;
}

int CPU::init()
{
 cout<<endl<<"CPU:";
 cout<<"\n\tProbing for CPU . . .";
 cpuid_vendor();
 cpuid_intel();
 return KMSG_SUCCESS;
}

void CPU::cpuid_vendor()
{
	int i;
	unsigned long unused, ebx, ecx, edx;
	cpuid(0, unused, ebx, ecx, edx);
	char vendor[13];
	vendor[12] = '\0';
	for (i = 0; i < 4; i++)
	{
		vendor[i]		= ebx >> (8 * i);
		vendor[i + 4]	= edx >> (8 * i);
		vendor[i + 8]	= ecx >> (8 * i);
	}
	cout<<"\n"<<vendor<<" ";
}

void CPU::cpuid_psn(void)
{
	unsigned int unused, eax, ecx, edx;
	cpuid(1, eax, unused, unused, unused);	// signature
	cpuid(3, unused, unused, ecx, edx);
	cout<<(eax >> 16)<<(eax & 0xFFFF)<<(ecx >> 16)<<(ecx & 0xFFFF)<<(edx >> 16)<< (edx & 0xFFFF);
}

void CPU::cpuid_features(void)
{
	unsigned long unused, edx;
	cpuid(1, unused, unused, unused, edx);
	cout<<"CPU Features:\n";
	if (edx & 0x00000001)	cout<<"\tFloating Point Unit\n";
	if (edx & 0x00000002)	cout<<"\tVirtual Mode Extensions\n";
	if (edx & 0x00000040)	cout<<"\tPhysical Address Extensions\n";
	if (edx & 0x00000200)	cout<<"\tOn-chip APIC\n";
	if (edx & 0x00040000)	cpuid_psn();
	if (edx & 0x40000000)	cout<<"\tIA-64 CPU\n";
	cpuid(0x80000001, unused, unused, unused, edx);
	cout<<"Extended Features: \n";
	if (edx & (1<<29))		cout<<"\tAMD64 Compliant\n";
}

void CPU::cpuid_detect(void)
{
	unsigned long eax, ebx, ecx, edx;
	cpuid(0, eax, ebx, ecx, edx);
	cpuid_vendor();
	switch (ebx)
	{
	case 0x756E6547:
		cpuid_intel();
		cpuid_features();
		break;
	case 0x68747541:
		break;
	default:
		cout<<"Unknown x86 CPU Detected\n";
		break;
	}
}

void CPU::cpuid_intel(void)
{
	unsigned long eax, ebx, ecx, edx, max_eax, unused, signature;
	int model, family, type, brand, stepping, reserved;
	int extended_family = -1;

	cpuid(1, eax, ebx, unused, unused);
	model		= (eax >> 4) & 0xF;
	family		= (eax >> 8) & 0xF;
	type		= (eax >> 12) & 0x3;
	brand		= (ebx & 0xFF);
	stepping	= (eax & 0xF);
	reserved	= (eax >> 14);
	signature	= (eax);

	switch (type)
	{
	case 0:
		cout<<"Original OEM ";
		break;
	case 1:
		cout<<"Overdrive ";
		break;
	case 2:
		cout<<"Dual Capable ";
		break;
	case 3:
		cout<<"Reserved ";
		break;
	}
	switch (family)
	{
	case 3:
		cout<<"i386\n";
		break;
	case 4:
		cout<<"i486\n";
		break;
	case 5:
		cout<<"Pentium\n";
		break;
	case 6:
		cout<<"Pentium Pro\n";
		break;
	case 15:
		cout<<"Pentium 4 ";
		break;
	}
	if(family == 15) 
	{
		extended_family = (eax >> 20) & 0xff;
		cout<<"Extended family \n"<<extended_family;
	}
	if (family != 15) 
	{
		cout<<"Model ";
		switch(family) 
		{
		case 3:
			break;
		case 4:
			switch(model)
			{
			case 0:
			case 1:
				cout<<"DX";
				break;
			case 2:
				cout<<"SX";
				break;
			case 3:
				cout<<"487/DX2";
				break;
			case 4:
				cout<<"SL";
				break;
			case 5:
				cout<<"SX2";
				break;
			case 7:
				cout<<"Write-back enhanced DX2";
				break;
			case 8:
				cout<<"DX4";
				break;
			}
			break;
		case 5:
				switch(model) 
				{
				case 1:
					cout<<"60/66";
					break;
				case 2:
					cout<<"75-200";
					break;
				case 3:
					cout<<"for 486 system";
					break;
				case 4:
					cout<<"MMX";
					break;
				}
			break;
		case 6:
			switch(model) 
			{
			case 1:
				cout<<"Pentium Pro";
				break;
			case 3:
				cout<<"Pentium II Model 3";
				break;
			case 5:
				cout<<"Pentium II Model 5/Xeon/Celeron";
				break;
			case 6:
				cout<<"Celeron";
				break;
			case 7:
				cout<<"Pentium III/Pentium III Xeon - external L2 cache";
				break;
			case 8:
				cout<<"Pentium III/Pentium III Xeon - internal L2 cache";
				break;
			}
			break;
		}
	}

	cpuid(0x80000000, max_eax, unused, unused, unused);
	if(brand > 0) 
	{
		cout<<"Brand - "<<brand;
		if(brand < 0x18) 
		{
			if(signature == 0x000006B1 || signature == 0x00000F13) 
			{
				cout<<Intel_Other[brand]<<"\n";
			} else {
				cout<<Intel[brand]<<"\n";
			}
		} else {
			cout<<"Reserved\n";
		}
	}
	cout<<"Stepping: "<<stepping<<" Reserved: "<<reserved<<"\n";
}


/* Print Registers */
void CPU::printregs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';
	for(j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}
	cout<<string;
}

CPU cpu;

#endif
