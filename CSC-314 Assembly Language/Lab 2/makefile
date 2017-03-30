# dependencies = fibonacci.asm iostream.asm stdlib.asm string.asm

# Lab 2 Program 1
lab2p1.o: lab2p1.asm
	nasm -f elf -g -F dwarf lab2p1.asm

lab2p1: lab2p1.o
	ld -m elf_i386 lab2p1.o -o lab2p1

# Lab 2 Program 1 Answer
lab2p1answer.o: lab2p1answer.asm
	nasm -f elf -g -F dwarf lab2p1answer.asm

lab2p1answer: lab2p1answer.o
	ld -m elf_i386 lab2p1answer.o -o lab2p1answer

# Lab 2 Program 2
lab2p2.o: lab2p2.asm
	nasm -f elf -g -F dwarf lab2p2.asm

lab2p2: lab2p2.o
	ld -m elf_i386 lab2p2.o -o lab2p2

lab2p1v2: lab2p1v2.o algorithmsv2.o
	ld -m elf_i386 lab2p1v2.o algorithmsv2.o -o lab2p1v2

lab2p1v2.o: lab2p1v2.asm
	nasm -f elf -g -F dwarf lab2p1v2.asm

algorithmsv2.o: algorithmsv2.asm
	nasm -f elf -g -F dwarf algorithmsv2.asm

clean:
	rm lab2p1 lab2p2 lab2p1answer lab2p2answer lab2p1v2 lab2p2v2 *.o -f
