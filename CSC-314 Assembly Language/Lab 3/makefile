# Lab 3 Program 

Lab0x03-main: Lab0x03-main.o libLab0x03.o
	ld -m elf_i386 Lab0x03-main.o libLab0x03.o -o Lab0x03-main

# main
main: libLab0x03.o
	g++ -m32 -g main.cpp libLab0x03.o -o main


Lab0x03-main.o: Lab0x03-main.asm
	nasm -f elf -g -F dwarf Lab0x03-main.asm

libLab0x03.o: libLab0x03.asm
	nasm -f elf -g -F dwarf libLab0x03.asm

clean:
	rm Lab0x03-main lab2p2 *.o -f
