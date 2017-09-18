%define link 0

%macro colon 2
	section .data
	%2:
	dq link
	db %1, 0
	%define link %2	
%endmacro



