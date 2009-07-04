#include "multiboot.h"
#include "iostream.h"

#if !defined ( __MULTIBOOT_GRUB_CPP_ )
#define __MULTIBOOT_GRUB_CPP_

unsigned int magic_global;
multiboot_info_t *mbi_global;

void print_multiboot_info(unsigned int magic, multiboot_info_t *mbi)
{
	cout<<"Multiboot Information:\n";
	cout<<"Magic: "<<magic;
	if (magic==MULTIBOOT_BOOTLOADER_MAGIC)
	{
		cout<<"Booted By Multiboot Loader\n";
//		cout<<"Flags: "<< mbi->flags;
		cout<<"Mem Lower:"<< (int)mbi->mem_lower;
		cout<<"\nMem upper:"<< (int)mbi->mem_upper;
		/*
		cout<<"Mem Upper = %d KB\n", mbi->mem_upper";
		cout<<"Boot Device = 0x%x\n", mbi->boot_device";*/
		cout<<"\nCommand Line"<<(char *)mbi->cmdline;
		/*cout<<"Modules Count = %d\n", mbi->mods_count";
		cout<<"Modules Address = 0x%x\n", mbi->mods_addr";
		cout<<"Mem Map length = %d\n", mbi->mmap_length";
		cout<<"Mem Map Address = 0x%x\n", mbi->mmap_addr;*/
	}
	else{
		cout<<"Not Loaded By Multiboot Loader";
	}
	cout<<"\n";
}

void print_memory_map(multiboot_info_t *mbi)
{
/*	unsigned long i, n;
	memory_map_t *mmap=(memory_map_t *)mbi->mmap_addr;
	n=mbi->mmap_length/sizeof(memory_map_t);
	cout<<"Memory Map:\n";
	for(i=0 ; i<n ; i++)
	{
		// Sized in not used here, it used to skip to the next pair 
		cout<<"Base Address=0x%x%x  ", (unsigned)mmap->base_addr_high, (unsigned)mmap->base_addr_low);
		cout<<"Length=0x%x%x  ", (unsigned)mmap->length_high, (unsigned)mmap->length_low);
		cout<<"Type=0x%x\n", (unsigned) mmap->type);
		mmap++;
	}*/
}

#endif
