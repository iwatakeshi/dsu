assemblipede: assemblipede.asm
	nasm -f elf -g -F dwarf assemblipede.asm
	ld -m elf_i386 assemblipede.o -o assemblipede  -lc -lncurses -I /lib/ld-linux.so.2 

# update: update.c
# 	gcc -g -m32 update.c -c

clean:
	rm -f *.o assemblipede