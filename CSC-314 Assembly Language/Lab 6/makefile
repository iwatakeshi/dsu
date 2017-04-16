# Lab 3 Program 

lab6: lab6.asm
	nasm -f elf -g -F dwarf lab6.asm
	ld -m elf_i386 lab6.o -o lab6 -lc -I /lib/ld-linux.so.2

clean:
	rm lab6 *.o -f
