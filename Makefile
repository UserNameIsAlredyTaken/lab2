lab2: clean lib.o dict.o main.o
	ld -o program main.o dict.o lib.o

main.o: main.asm colon.inc words.inc
	nasm -f elf64 -o main.o main.asm

lib.o: lib.inc
	nasm -f elf64 -o lib.o lib.inc

dict.o: dict.asm
	nasm -f elf64 -o dict.o dict.asm

clean:
	rm main.o dict.o lib.o program