dependencies = fibonacci.asm iostream.asm stdlib.asm string.asm

lab1: lab1.o
	ld -m elf_i386 lab1.o -o lab1

lab1.o: lab1.asm $(dependencies)
	nasm -f elf -g -F dwarf lab1.asm
	
clean:
	rm lab1 *.o
