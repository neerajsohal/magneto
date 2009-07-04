#include "iostream.h"
#include "kore\kmsgs.h"

#if !defined ( __GDT_H_ )
#define __GDT_H_

class GDT
{
	private:
	struct gdt_entry_struct
	{
		unsigned short limit_low;           // The lower 16 bits of the limit.
		unsigned short base_low;            // The lower 16 bits of the base.
		unsigned char  base_middle;         // The next 8 bits of the base.
		unsigned char  access;              // Access flags, determine what ring this segment can be used in.
		unsigned char  granularity;
		unsigned char  base_high;           // The last 8 bits of the base.
	} __attribute__((packed));
	typedef struct gdt_entry_struct gdt_entry_t; 
	struct gdt_ptr_struct
	{
		unsigned short limit;               // The upper 16 bits of all selector limits.
		unsigned int base;                // The address of the first gdt_entry_t struct.
	} __attribute__((packed));
	typedef struct gdt_ptr_struct gdt_ptr_t;
	void init_gdt();
	void gdt_set_gate(int, unsigned int, unsigned, unsigned char, unsigned char);

	gdt_entry_t gdt_entries[5];
	gdt_ptr_t   gdt_ptr;
	
	public:
		GDT();
		~GDT();
		int init();
};

extern GDT gdt;

#endif
