#include "GDT.h"

#if !defined ( __GDT_CPP_ )
#define __GDT_CPP_

extern "C" void gdt_flush(unsigned int);

GDT gdt;

GDT::GDT()
{
 ;
}

GDT::~GDT()
{
 ;
}

void GDT::init_gdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (unsigned int)&gdt_entries;

   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush((unsigned int)&gdt_ptr);
}

// Set the value of one GDT entry.
void GDT::gdt_set_gate(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

int GDT::init()
{
 cout<<endl<<"GDT:";
 cout<<"\n\tInitializing . . .";
 init_gdt();
 cout<<"\n\tInstalled new GDT";
 return KMSG_SUCCESS;
}

#endif
