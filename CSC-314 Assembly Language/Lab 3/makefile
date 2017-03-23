# dependencies = fibonacci.asm iostream.asm stdlib.asm string.asm

# Lab 2 Program 1

Lab0x03-main: Lab0x03-main.o
	ld -m elf_i386 Lab0x03-main.o -o Lab0x03-main

Lab0x03-main.o: Lab0x03-main.asm
	nasm -f elf -g -F stabs Lab0x03-main.asm



clean:
	rm Lab0x03-main lab2p2 *.o -f
