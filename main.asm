%include "words.inc"

section .data

error_msg: db 'Sorry, but no :(', 10 ;сообщение в случае не нахождения элемента

section .text

extern find_word
extern print_string
extern string_length
extern read_string

global _start

_start:
	.loop:
		call read_string ; читаем строку с stdin до символа переноса строки
		mov rdi, rax ; помещаем в rdi указатель на word_buffer с введённой строкой
		mov rsi, link ; помещаем в rsi указатель на последний элемент списка
		call find_word ; вызываем find_word
		test rax,rax ; поверяем вывод find_word на 0
	
		je .error ; если 0, значит слово не найдено
	
		mov rdi, rax ; помещаем в rdi указатель на метку ескомой записи
		add rdi, 8 ; перемещаем указатель на ключ искомой записи
		call string_length ; считываеем количество символов в ключе
		add rdi, rax ; перемещаем указатель на конец ключа (0 нультерминированной строки)
		inc rdi ; помещаем указатель на начало значения записи
		call print_string ; выводим значение
	
.end:
	mov rax, 60 ; завершаем работу программы
	xor rdi, rdi
	syscall
	
.error:
	mov rax, 1 ; выводим сообщение об ошибке
	mov rdi, 2
	mov rsi, error_msg
	mov rdx, 43
	syscall
	
	jmp .end 
	
	