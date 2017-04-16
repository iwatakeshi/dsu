# Lab 3 Program 

# main
# main: libLab0x04.o
	# g++ -m32 -g main.cpp libLab0x04.o -o main
main: Lab0x04-main.c libLab0x04
	gcc -m32 -g Lab0x04-main.c libLab0x04.o -o Lab0x04-main

libLab0x04: libLab0x04.o
	ld -e _sumAndPrintList -m elf_i386 libLab0x04.o -o Lab0x04 -lc

libLab0x04.o: libLab0x04.asm
	nasm -f elf -g -F dwarf libLab0x04.asm

clean:
	rm Lab0x04-main main *.o -f
