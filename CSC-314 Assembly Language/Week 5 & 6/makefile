dependencies = iostream.asm stdlib.asm string.asm

digitcount: digitcount.o
	ld -m elf_i386 -e main digitcount.o -o digitcount

digitcount.o: digitcount.asm $(dependencies)
	nasm -f elf -g -F dwarf digitcount.asm

clean:
	rm digitcount *.o
