section .test
extern string_equals
;rdi-��������� �� �������� ����
;rsi-��������� �� ��������� ����� � �������
global find_word
find_word:
	.loop:
		push rsi
		push rdi
		add rsi, 8
		call string_equals
		push rdi
		pop rsi
		
		test rax, rax
		jnz .finish
		mov rsi, [rsi]
		test rsi, rsi
		jnz .loop 
		xor rax, rax
		ret
	.finish:
		mov rax, rsi	
	ret
	