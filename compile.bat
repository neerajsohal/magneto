nasm -f aout -o Obj\Kore\KStart.o Kore\KStart.asm

CD Lib
CD String
gcc -o strlen.o strlen.cpp -c -I..\..\Include -nostdinc++ -fno-builtin -fno-exceptions -fno-rtti
MOVE strlen.o ..\..\obj\Lib\String
gcc -o strcmp.o strcmp.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE strcmp.o ..\..\obj\Lib\String
gcc -o strcpy.o strcpy.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE strcpy.o ..\..\obj\Lib\String
CD ..\mem
gcc -o memset.o memset.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE memset.o ..\..\obj\Lib\mem
gcc -o memcpy.o memcpy.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE memcpy.o ..\..\obj\Lib\mem
CD ..
gcc -o ctype.o ctype.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE ctype.o ..\obj\Lib\
gcc -o math.o math.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE math.o ..\obj\Lib\
gcc -o OStream.o OStream.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti -O3
MOVE OStream.o ..\obj\Lib\
gcc -o IStream.o IStream.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti -O3
MOVE IStream.o ..\obj\Lib\
gcc -o conio.o conio.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti -O3
MOVE conio.o ..\obj\Lib\
CD ..

CD Kore
gcc -o Kore.o Kore.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE Kore.o ..\obj\Kore\
gcc -o delay.o delay.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE delay.o ..\obj\Kore\
gcc -o Support.o Support.c -c
MOVE Support.o ..\obj\Kore\
gcc -o multiboot_grub.o multiboot_grub.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE multiboot_grub.o ..\obj\Kore\
gcc -o system.o system.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE system.o ..\obj\Kore\
CD ..

CD Silver
gcc -o Silver.o Silver.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE Silver.o ..\obj\Silver\
CD ..

CD Drivers\Sound\PC_Speaker
gcc -o PC_Speaker.o PC_Speaker.cpp -c -I..\..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE PC_Speaker.o ..\..\..\obj\Drivers\Sound\PC_Speaker\
CD ..\..\Video\VGA
gcc -o VGA.o VGA.cpp -c -I..\..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE VGA.o ..\..\..\obj\Drivers\Video\VGA\
CD ..\..\Video\Console
gcc -o Console.o Console.cpp -c -I..\..\..\Include -fno-builtin -fno-exceptions -fno-rtti -O3
MOVE Console.o ..\..\..\obj\Drivers\Video\Console\
CD ..\..\Keyboard
gcc -o Keyboard.o Keyboard.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE Keyboard.o ..\..\obj\Drivers\Keyboard\
gcc -o KB_IRQ.o KB_IRQ.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE KB_IRQ.o ..\..\obj\Drivers\Keyboard\
gcc -o KB_BUF.o KB_BUF.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE KB_BUF.o ..\..\obj\Drivers\Keyboard\
CD ..\FDC
gcc -o FDC.o FDC.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE FDC.o ..\..\obj\Drivers\FDC\
gcc -o FDC_IRQ.o FDC_IRQ.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE FDC_IRQ.o ..\..\obj\Drivers\FDC\
CD ..\PIT
gcc -o PIT.o PIT.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE PIT.o ..\..\obj\Drivers\PIT\
gcc -o PIT_irq.o PIT_irq.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE PIT_irq.o ..\..\obj\Drivers\PIT\
CD ..\FAT
gcc -o FAT.o FAT.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE FAT.o ..\..\obj\Drivers\FAT\
CD ..
CD ..

CD Arch\x86
gcc -o x86.o x86.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE x86.o ..\..\obj\Arch\x86\
gcc -o GDT.o GDT.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE GDT.o ..\..\obj\Arch\x86\
nasm -f coff -o gdt_stub.o gdt_stub.asm
MOVE gdt_stub.o ..\..\obj\Arch\x86\
gcc -o Interrupts.o Interrupts.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti -O3
MOVE Interrupts.o ..\..\obj\Arch\x86\
gcc -o cpuid.o cpuid.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE cpuid.o ..\..\obj\Arch\x86\
gcc -o cmos.o cmos.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE cmos.o ..\..\obj\Arch\x86\
CD ..
CD ..

CD Shell
gcc -o Shell.o Shell.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell.o ..\obj\Shell
gcc -o shell_cmds.o shell_cmds.cpp -c -I..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmds.o ..\obj\Shell
CD commands
gcc -o shell_cmd_ver.o shell_cmd_ver.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_ver.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_help.o shell_cmd_help.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_help.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_logout.o shell_cmd_logout.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_logout.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_date.o shell_cmd_date.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_date.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_time.o shell_cmd_time.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_time.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_floppy.o shell_cmd_floppy.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_floppy.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_cmos.o shell_cmd_cmos.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_cmos.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_halt.o shell_cmd_halt.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_halt.o ..\..\obj\Shell\Commands
gcc -o shell_cmd_system.o shell_cmd_system.cpp -c -I..\..\Include -fno-builtin -fno-exceptions -fno-rtti
MOVE shell_cmd_system.o ..\..\obj\Shell\Commands
CD ..
CD ..

ld -o bin\Kore.bin -T scripts\link.ld -O3

COPY bin\Kore.bin a:\magneto\kore.bin

pause