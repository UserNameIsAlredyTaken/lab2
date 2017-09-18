%include "colon.inc"
%include "words.inc"

section .data

error_msg: db 'Не удалось найти значение по данному ключу', 10

section .text

extern read_word
extern find_word
extern print_string

global _start

_start:
	call read_word
	mov rdi, rax
	mov rsi, link
	call find_word
	test rax,rax
	
	je .error
	
	mov rdi, rax
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
	
	