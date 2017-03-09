# dependencies = fibonacci.asm iostream.asm stdlib.asm string.asm

# Lab 2 Program 1
lab2p1.o: lab2p1.asm
	nasm -f elf -g -F dwarf lab2p1.asm

lab2p1: lab2p1.o
	ld -m elf_i386 lab2p1.o -o lab2p1

# Lab 2 Program 2
lab2p2.o: lab2p2.asm
	nasm -f elf -g -F dwarf lab2p2.asm

lab2p2: lab2p2.o
	ld -m elf_i386 lab2p2.o -o lab2p2



clean:
	rm lab2p1 lab2p2 *.o -f
