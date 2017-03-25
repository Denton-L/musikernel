		.set ALIGN,		1 << 0
		.set MEMINFO,		1 << 1
		.set FLAGS,		ALIGN | MEMINFO
		.set MAGIC,		0x1BADB002
		.set CHECKSUM,		-(MAGIC + FLAGS)

		.section .header
		.balign 4
		.long MAGIC
		.long FLAGS
		.long CHECKSUM

		.section .bss
		.balign 16
s_bottom:
		.skip 16384					# Reserve 16 KiB of memory for the stack
s_top:

		.section .text
		.global _start
		.type _start, @function
_start:
		mov $s_top, %esp
		# TODO: initialize processor state here
		call main

		cli
hltloop:	hlt
		jmp hltloop

		.size _start, . - _start
