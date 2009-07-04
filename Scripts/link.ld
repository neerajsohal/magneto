/* Link.ld */
OUTPUT_FORMAT("binary")
ENTRY(start)
SECTIONS
{
.text 0x100000 :
{
code = .; _code = .; __code = .;
*(.text)
. = ALIGN(4096);
}

.data :
{
__CTOR_LIST__ = .; LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2) *(.ctors) LONG(0) __CTOR_END__ = .; 
__DTOR_LIST__ = .; LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2) *(.dtors) LONG(0) __DTOR_END__ = .;

data = .; _data = .; __data = .;
*(.data)
. = ALIGN(4096);
}

.bss :
{
bss = .; _bss = .; __bss = .;
*(.bss)
. = ALIGN(4096);
}

end = .; _end = .; __end = .;
}

INPUT (
obj\kore\kstart.o obj\kore\support.o obj\kore\kore.o obj\kore\delay.o obj\kore\multiboot_grub.o obj\kore\system.o
obj\arch\x86\x86.o obj\arch\x86\gdt.o obj\arch\x86\gdt_stub.o obj\arch\x86\interrupts.o obj\arch\x86\cpuid.o obj\arch\x86\cmos.o
obj\drivers\video\console\console.o obj\drivers\video\vga\vga.o obj\drivers\pit\pit.o obj\drivers\pit\pit_irq.o obj\drivers\fat\fat.o
obj\drivers\keyboard\keyboard.o obj\drivers\keyboard\kb_buf.o obj\drivers\keyboard\kb_irq.o
obj\drivers\fdc\fdc.o obj\drivers\fdc\fdc_irq.o
obj\lib\ostream.o obj\lib\mem\memset.o obj\lib\string\strcpy.o obj\lib\string\strlen.o obj\lib\mem\memcpy.o obj\lib\ctype.o obj\lib\istream.o obj\lib\string\strcmp.o obj\lib\conio.o
obj\shell\shell.o obj\shell\shell_cmds.o obj\shell\commands\shell_cmd_ver.o obj\shell\commands\shell_cmd_help.o obj\shell\commands\shell_cmd_logout.o obj\shell\commands\shell_cmd_date.o obj\shell\commands\shell_cmd_cmos.o obj\shell\commands\shell_cmd_time.o obj\shell\commands\shell_cmd_floppy.o obj\shell\commands\shell_cmd_halt.o obj\shell\commands\shell_cmd_system.o
);
