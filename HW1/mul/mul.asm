		section		.text

		global		_start
_start:
		sub		rsp,		4 * 128 * 8
		lea		rdi,		[rsp + 128 * 8]
		mov		rcx,		128
		call		read_long
		mov		rdi,		rsp
		call		read_long
		lea		rsi,		[rsp + 128 * 8]
; rdi -- #1 [rsp]
; rsi -- #2 [rsp + 128 * 8]
; rcx -- length
		lea		r9,		[rsp + 2 * 128 * 8]

; r9 -- [rsp + 2 * 128 * 8]

		call		copy_long

		lea		r10,		[rsp + 3 * 128 * 8]

; r10 -- [rsp + 3 * 128 * 8]
		
		mov		r15,		rdi
		mov		rdi,		r10
		call		set_zero
		mov		r10,		rdi
		mov		rdi,		r15

		call		mul_long_long
				
		call		write_long

		mov		al,		0x0a
		call		write_char

		jmp		exit

; rdi -- src
; r9 -- dst
; rcx -- length

copy_long:
		push		rdi
		push		r9
		push		rcx
		push		rax
.loop:
		mov		rax,		[rdi]
		mov		[r9], 		rax
		lea		r9,		[r9 + 8]
		lea		rdi,		[rdi + 8]
		dec		rcx
		jnz 		.loop

		pop		rax
		pop		rcx
		pop		r9
		pop		rdi
		ret
	
mul_long_long:
		push		rdi
		push		rsi
		push		rcx
		
		clc
.loop:
		mov		rbx,		[rsi]
		lea		rsi,		[rsi + 8]
		call 		mul_long_short

; r10 += rdi
		mov		r15,		rdi
		mov		r14,		rsi
		mov		rsi,		rdi
		mov		rdi,		r10
		call		add_long_long
		mov		r10,		rdi
		mov		rdi,		r15
		mov		rsi,		r14


		mov		r15,		rdi
		mov		rdi,		r9
		mov		rbx, 		0x100000000
		call		mul_long_short
		call		mul_long_short
		mov		r9,		r15
		call		copy_long
		mov		r9,		rdi
		mov		rdi,		r15
		
		dec		rcx
		jnz		.loop

		pop		rcx
		push		rcx

		mov		r15,		rdi
		mov		r9,		rdi
		mov		rdi,		r10
		call 		copy_long
		mov		rdi,		r15
	
		pop		rcx
		pop		rsi
		pop		rdi
		ret

add_long_long:
		push		rdi
		push		rsi
		push		rcx

		clc
.loop:
		mov		rax, 		[rsi]
		lea		rsi,		[rsi + 8]
		adc		[rdi],		rax
		lea		rdi,		[rdi + 8]
		dec		rcx
		jnz		.loop

		pop		rcx
		pop		rsi
		pop		rdi
		ret

add_long_short:
		push		rdi
		push		rcx
		push		rdx
		
		xor		rdx,		rdx
.loop:
		add		[rdi],		rax
		adc		rdx,		0
		mov		rax,		rdx
		xor		rdx,		rdx
		add		rdi,		8
		dec		rcx
		jnz		.loop

		pop		rdx
		pop		rcx
		pop		rdi
		ret

mul_long_short:
		push		rax
		push		rdi
		push		rcx
		push		rsi

		xor		rsi,		rsi
.loop:
		mov		rax,		[rdi]
		mul		rbx
		add		rax,		rsi
		adc		rdx,		0
		mov		[rdi],		rax
		add		rdi,		8
		mov		rsi,		rdx
		dec		rcx
		jnz		.loop

		pop		rsi
		pop		rcx
		pop		rdi
		pop		rax
		ret

div_long_short:
		push		rdi
		push		rax
		push		rcx

		lea		rdi,		[rdi + 8 * rcx - 8]
		xor		rdx,		rdx
.loop:
		mov		rax,		[rdi]
		div		rbx
		mov		[rdi],		rax
		sub		rdi,		8
		dec		rcx
		jnz		.loop

		pop		rcx
		pop		rax
		pop		rdi
		ret

; rdi -- number
; rcx -- length

set_zero:
		push		rax
		push		rdi
		push		rcx

		xor		rax,		rax
		rep		stosq
		
		pop		rcx
		pop		rdi
		pop		rax
		ret
is_zero:
		push		rax
		push		rdi
		push		rcx

		xor		rax,		rax
		rep		scasq

		pop		rcx
		pop		rdi
		pop		rax
		ret

read_long:
		push		rcx
		push		rdi

		call		set_zero
.loop:
		call		read_char
		or		rax,		rax
		js		exit
		cmp		rax,		0x0a
		je		.done
		cmp		rax, 		'0'
		jb		.invalid_char
		cmp		rax,		'9'
		ja		.invalid_char

		sub		rax,		'0'
		mov		rbx,		10
		call		mul_long_short
		call		add_long_short
		jmp		.loop

.done:
		pop		rdi
		pop		rcx
		ret

.invalid_char:
		mov		rsi,		invalid_char_msg
		mov		rdx,		invalid_char_msg_size
		call		print_string
		call		write_char
		mov		al,		0x0a
		call		write_char

.skip_loop:
		call		read_char
		or		rax,		rax
		js		exit
		cmp		rax,		0x0a
		je		exit
		jmp		.skip_loop

write_long:
		push		rax
		push		rcx
		
		mov		rax,		20
		mul		rcx
		mov		rbp,		rsp
		sub		rsp,		rax

		mov		rsi,		rbp
.loop:
		mov		rbx,		10
		call		div_long_short
		add		rdx,		'0'
		dec		rsi
		mov		[rsi],		dl
		call		is_zero
		jnz		.loop

		mov		rdx,		rbp
		sub		rdx,		rsi
		call		print_string

		mov		rsp,		rbp
		pop		rcx
		pop		rax
		ret

read_char:
		push		rcx
		push		rdi
	
		sub		rsp,		1
		xor		rax,		rax
		xor		rdi,		rdi
		mov		rsi,		rsp
		mov		rdx,		1
		syscall

		cmp		rax,		1
		jne		.error
		xor		rax,		rax
		mov		al, 		[rsp]
		add		rsp,		1
	
		pop		rdi
		pop		rcx
		ret
.error:
		mov		rax,		-1
		add		rsp,		1
		pop		rdi
		pop		rcx
		ret

write_char:
		sub		rsp,		1
		mov		[rsp], 		al
		
		mov		rax,		1
		mov		rdi,		1
		mov		rsi,		rsp
		mov		rdx,		1
		syscall
		add		rsp,		1
		ret

exit:
		mov		rax,		60
		xor		rdi,		rdi
		syscall

print_string:
		push		rax

		mov		rax,		1
		mov		rdi,		1
		syscall

		pop		rax
		ret


		section		.rodata
invalid_char_msg:
		db		"Invalid charater: "
invalid_char_msg_size:	equ		$ - invalid_char_msg

