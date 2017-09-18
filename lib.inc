section .text
string_length: 
	xor rax, rax ;внесение в rax 0, чтобы использовать как счётчик
	.loop:
		cmp byte[rdi + rax], 0 ;проверка каждого байта в цикле на 0
		je .finish
		inc rax ;увеличение счётчика
		jmp .loop
	.finish:			
    ret

global print_string

print_string:	
	push rax
	
    mov rsi, rdi ;внесение адреса начала строки
	call string_length ;внесение в rax длинны строки
	mov rdx, rax
	mov rax, 1		
	mov rdi, 1
	
	push rcx
	syscall
	pop rcx
	
	pop rax	
    ret

print_char:
	push rax	
	push rdi ;внесение адреса в стек
	
	mov rax, 1	
	mov rdi, 1
	mov rsi, rsp ;запись адоеса из стека
	mov rdx, 1
	
	push rcx
	syscall
	pop rcx
	
	pop rdi	
	pop rax
	ret

print_newline:
    push rdi
	
	mov rdi, 10 ;запись символа переноса в каестве аргумента для print_char
	call print_char
	
	pop rdi
    ret


print_uint:
    mov r8, rsp ;сохраняем адрес вершины стека
	
	mov r10, 10 ;записываем делитель
	mov rax, rdi ;записывем делимое
	dec rsp ;записываем в rsp адоес ячейки над стеком
	mov byte[rsp], 0 ; записываем символ окончания строки
	.loop:
		xor rdx, rdx ;зануляем rdx(сюда пойдёт остаток)
		div r10 ;делим число в rsp на 10, остаток в dl
		dec rsp
		add dl, '0' ;прибовляем к остатку код нуля, чтобы получить код ASCII
		mov [rsp], dl ;заносим остаток в стек
		test rax, rax ;проверяем, осталось ли что-нибудь от числа
		jnz .loop
	mov rdi, rsp ;записываем в аргумент начало строки
	call print_string ;выводим число	
	
	mov rsp, r8 ;восстанавливаем адрес вершины стека
    ret


print_int:
    test rdi, rdi ;проверяем число на знак
	jns .pozitive ;если положительное, то просто выводим
	push rdi ;сохраняем значение
	mov rdi, '-' ;в аргумент записываем знак "-"
	call print_char ;выводим аргумент
	pop rdi ;восстанавливаем прежнее значение
	neg rdi	;инвертируем значение
	.pozitive:		
		call print_uint	;выводим значение	
    ret

read_char:
	push 0 ;заносим в стек символ на случай если ничего не придёт на вход
	
	mov rax, 0 ;записываем номер системный вызов "read"
	mov rdi, 0 ;дескриптор stdin
	mov rsi, rsp ;запишем символ в стек
	mov rdx, 1 ;количество байт для чтения
	
	push rcx
	syscall
	pop rcx
	
	pop rax ;запишем в rax пришедший символ или 0	
    ret 

section .data
word_buffer times 256 db 0

section .text

global read_word
read_word:
	mov r8, word_buffer ;запись адреса в r8

.begin_spase:
	call read_char
	test rax, rax ;проверка на пустую строку
	je .end_space
	cmp rax, ' ' ;проверка на пробел
	jle .begin_spase
.write:
	mov [r8], rax ; запись символа
	inc r8 ;увеличение адреса
	call read_char
	cmp rax, ' ' ;проверка на пробел
	jg .write
.end_space:
	xor r9, r9 ;запись 0 в конец строки
	mov [r8], r9
	mov rax, word_buffer ;запись в rax адреса буфера
	sub r8, rax ;запись в rdx длинны слова
	mov rdx, r8
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
	mov r10, 10 ;заносим множитель
	xor r8, r8 ;обнуляем переменные
	xor rax, rax
	xor rcx, rcx
	.loop:
		cmp byte[rdi+rcx], '0' ;проверяем на цифру
		jb .ending
		cmp byte[rdi+rcx], '9'
		ja .ending
		mov r8b, byte[rdi+rcx] ;записываем цифру в r8
		sub r8, '0' ;приводим цифру(не ASCII)
		mul r10 ;домножаем всё число на 10 
		add rax, r8 ;прибовляем к числу новую цифру
		inc rcx ;увеличиваем счётчик
		jmp .loop
	.ending:
	mov rdx, rcx
    ret	
	
; rdi points to a string
; returns rax: number, rdx : length
parse_int:	
	cmp byte[rdi], '-' ;проверяем число на отрицательность
	je .negative
	call parse_uint ;если положительное, то просто юзаем parse_uint
	ret
	.negative:
		inc rdi ;так как число отрицательное, надо учитывать минус
		call parse_uint
		neg rax ;инвертируем полученное число
		inc rdx
    ret 
	
global string_equals
string_equals:
	xor rax, rax ;зануляем переменные
	xor r8, r8
	xor r9, r9
	xor rcx, rcx
	.loop:
		mov r8b, byte[rdi+rcx] ;посимвольно сравниваем строки
		mov r9b, byte[rsi+rcx]
		cmp r8, r9
		jne .uniq ;если не равны
		inc rcx ;увеличиваем счётчик символов
		cmp r8, 0 ;смотрим, что строка не закончилась
		jne .loop		
	mov rax, 1
	ret	
	.uniq:
    ret
	
string_copy:
	xor rcx, rcx
	.loop:
		xor r8, r8
		mov r8b, byte[rdi+rcx] ;через посредник посимвольно копируем строку в яч. памяти
		mov byte[rsi+rcx], r8b
		inc rcx ;увеличиваем счётчик символов
		test r8, r8 ;проверяем, что не конец строки
		jnz .loop
	ret