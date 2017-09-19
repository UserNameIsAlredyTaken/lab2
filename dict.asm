section .text
extern string_equals
;rdi-указатель на искомыый ключ
;rsi-указатель на последнее слово в словаре
global find_word
find_word:
	.loop:
		push rsi
		push rdi
		add rsi, 8 ; rsi указывал на метку предыдущего элемента, переходим на ключ
		call string_equals ; сравниваем ключ с тем, что у нас лежит в word_buffer
		pop rdi
		pop rsi		
		test rax, rax	; проверяем, результат функции string_equals
		
		jnz .finish
		mov rsi, [rsi] ; помещаем в rsi ссылку на предыдущий элемент
		test rsi, rsi ; проверяем, не равна ли эта ссылка 0
		jnz .loop 
		xor rax, rax ;если равна, возвращаем 0
		ret
		
	.finish: ; возвращаем указатель на метку искомой записи
		mov rax, rsi	
	ret
	