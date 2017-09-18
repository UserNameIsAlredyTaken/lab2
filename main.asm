%include "words.inc"

section .data

error_msg: db 'Sorry, but no :(', 10

section .text

extern find_word
extern print_string
extern string_length
extern read_string

global _start

_start:
	.loop:
		call read_string
		mov rdi, rax
		mov rsi, link
		call find_word
		test rax,rax
	
		je .error
	
		mov rdi, rax
		add rdi, 8
		call string_length
		add rdi, rax
		inc rdi
		call print_string	
	
.end:
	mov rax, 60
	xor rdi, rdi
	syscall
	
.error:
	mov rax, 1
	mov rdi, 2
	mov rsi, error_msg
	mov rdx, 43
	syscall
	
	jmp .end
	
	