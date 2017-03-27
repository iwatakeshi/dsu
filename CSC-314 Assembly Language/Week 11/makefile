# dependencies = iostream.asm stdlib.asm string.asm

# cdecl
cdecl: cdecl.o libexample.o
	ld -m elf_i386 -e _start cdecl.o libexample.o -o cdecl

# main
main: libexample.o
	gcc -m32 main.c libexample.o -o main

cdecl.o: cdeclexample.asm
	nasm -f elf -g -F dwarf cdeclexample.asm -o cdecl.o

libexample.o: libexample.asm
	nasm -f elf -g -F dwarf libexample.asm


clean:
	rm cdecl *.o
