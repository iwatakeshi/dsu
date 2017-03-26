# dependencies = iostream.asm stdlib.asm string.asm

# try.stack
stack: stack.o libintio.o
	ld -m elf_i386 -e _start stack.o libintio.o -o stack

stack.o: stack.asm
	nasm -f elf -g -F dwarf stack.asm

libintio.o: libintio.asm
	nasm -f elf -g -F dwarf libintio.asm

clean:
	rm stack *.o
