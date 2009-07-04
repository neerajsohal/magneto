# i386/cmos.asm
# Copyrights (c) 2005-2007 Mohamed Abdelsalam Aslan <maslan@users.berlios.de>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

.global	_cmos_read
.global	_cmos_write

# Copy the 64bytes from CMOS to [ebp+08]
# [ebp+08] pointer to cmos_t struct
_cmos_read:
	cli
	pushl		%ebp
	movl		%esp, %ebp
	pushl		%eax
	pushl		%ebx
	pushl		%ecx
	pushfl
	movl		8(%ebp), %ebx
read_updating:
	movb		$0xa, %al
	outb		%al, $0x70
	inb		$0x71, %al
	testb		$0x80, %al
	jne		read_updating
# Copy from CMOS
	xorb		%cl, %cl
read_copy_cmos:
	movb		%cl, %al
	outb		%al, $0x70
	inb		$0x71, %al  	
	movb		%al, (%ebx)
	cmpb		$0x3f, %cl
	je		read_copy_finish	
	incl		%ebx
	incb		%cl
	jmp		read_copy_cmos
# Finished
read_copy_finish:
	popfl
	popl		%ecx
	popl		%ebx
	popl		%eax
	movl		%ebp, %esp
	pop		%ebp
	sti
	ret


# Copy 64byte from [ebp+08] to CMOS
# [ebp+08] pointer to cmos_t struct
osdk_cmos_write:
	cli
	pushl		%ebp
	movl		%esp, %ebp
	pushl		%eax
	pushl		%ebx
	pushl		%ecx
	pushfl
	movl		8(%ebp), %ebx
write_updating:
	movb		$0xa, %al
	outb		%al, $0x70
	inb		$0x71, %al
	testb		$0x80, %al
	jne		write_updating
# Copy to CMOS
	xorb		%cl, %cl
write_copy_cmos:
	movb		%cl, %al
	outb		%al, $0x70
	movb		(%ebx), %al
	outb		%al, $0x71  
	cmpb		$0x3f, %cl
	je		write_copy_finish	
	incl		%ebx
	incb		%cl
	jmp		write_copy_cmos
# Finished
write_copy_finish:
	popfl
	popl		%ecx
	popl		%ebx
	popl		%eax
	mov		%ebp, %esp
	pop		%ebp
	sti
	ret

