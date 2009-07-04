;	Module Name: 
;	File Name: /Kore/KStart.asm
;	Decription: Transfers Control To Main Kernel
;	Last Modified: 01 Jan' 2008

[BITS 32] ; protected mode

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Multiboot header for GRUB bootloader. This must be in the first 8K
; of the kernel file. We use the aout kludge so it works with ELF,
; DJGPP COFF, Win32 PE, or other formats.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MULTIBOOT_PAGE_ALIGN	equ 1<<0
MULTIBOOT_MEMORY_INFO	equ 1<<1
MULTIBOOT_AOUT_KLUDGE	equ 1<<16
MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

; these are in the linker script file
EXTERN code, bss, end

ALIGN 4
mboot:
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM
; aout kludge. These must be PHYSICAL addresses
	dd mboot
	dd code
	dd bss
	dd end
	dd entry

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; entry point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
entry:
 
[global start] 
[extern __main] 	; this is our C support code
[extern _main] 		; this is our C++ code
[extern __atexit]

start:

	push ebx		; Load multiboot information:
	push eax;		;Load multiboot Magic Number
	call __main
	call _main 		; call our C++ code
	call __atexit
	jmp $			; Hang
	
SECTION .data

SECTION .text

SECTION .bss
	resd 4096
stack:
