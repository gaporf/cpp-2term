		section		.text

		global		_start
_count:
.loop:
		dec		rax
		cmp		[buf+rax],	r12b
		jl		.first
		cmp		[buf+rax],	r13b
		jg		.first
		cmp		r11,		1
		je		.end_loop
		inc		r15
		mov		r11, 		1
		jmp		.end_loop
.first:		
		cmp		[buf+rax],	r14b
		jne		.second
		cmp		r11,	1
		je		.end_loop
		inc		r15
		mov		r11,	1
		jmp		.end_loop
.second:
		xor		r11,		r11
.end_loop:
		cmp		rax,		0
		jg		.loop
		ret

_print_number:
		xor		r9,		r9
		mov		rax,		r15
		mov		rbx,		10
.loop:
		xor		rdx,		rdx
		div		rbx
		push		rdx
		inc		r9
		cmp		rax,	0
		jg		.loop

		xor		r10,		r10
.loop_2:
		pop		r11
		add		r11,		48
		mov		[buf+r10],	r11
		inc		r10
		dec		r9
		jg		.loop_2

		mov		r11,		10
		mov		[buf+r10],	r11
		inc		r10
		mov		rax,		1
		mov		rdi,		1
		mov		rsi,		buf
		mov		rdx,		r10
		syscall

		ret
_start:
		xor		r11,		r11
		mov		r12,		9
		mov		r13,		13
		mov		r14,		32
		xor		r15,		r15

		pop		rax
		cmp		rax, 		2
		jne		_error

		pop		rax
		pop		rdi
		mov		rax,		2
		xor		rsi, 		rsi
		xor		rdx,		rdx
		syscall		
		
		mov		rdi,		rax
.loop:
		xor		rax, 		rax
		mov		rsi, 		buf
		mov		rdx,		1024
		syscall
		
		cmp		rax, 		0
		je		_end
		call		_count
		jmp		.loop

_end:
		call		_print_number

		mov		rax,		60
		xor		rdi, 		rdi
		syscall

_error:
		mov		rax,		1
		mov		rdi,		2
		mov		rsi,		error_msg
		mov		rdx,		msg_size
		syscall

		section		.rodata
error_msg:	db	"Invalid number of arguments", 0x0a
msg_size:	equ	$ - error_msg
		
		section		.bss

buf:		resb		1024
