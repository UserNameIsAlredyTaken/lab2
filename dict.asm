section .text
extern string_equals
;rdi-��������� �� �������� ����
;rsi-��������� �� ��������� ����� � �������
global find_word
find_word:
	.loop:
		push rsi
		push rdi
		add rsi, 8 ; rsi �������� �� ����� ����������� ��������, ��������� �� ����
		call string_equals ; ���������� ���� � ���, ��� � ��� ����� � word_buffer
		pop rdi
		pop rsi		
		test rax, rax	; ���������, ��������� ������� string_equals
		
		jnz .finish
		mov rsi, [rsi] ; �������� � rsi ������ �� ���������� �������
		test rsi, rsi ; ���������, �� ����� �� ��� ������ 0
		jnz .loop 
		xor rax, rax ;���� �����, ���������� 0
		ret
		
	.finish: ; ���������� ��������� �� ����� ������� ������
		mov rax, rsi	
	ret
	