assemblipede: assemblipede.asm
	nasm -f elf -g -F dwarf assemblipede.asm
	ld -m elf_i386 assemblipede.o -o assemblipede  -lc -lncurses -I /lib/ld-linux.so.2 

clean:
	rm -f *.o assemblipede