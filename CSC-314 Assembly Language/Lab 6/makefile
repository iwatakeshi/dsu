# Lab 6

# Build all
all: lab0x06-Problem2-main lab0x06-HackMe input

# Disassemble
disassemble-problem2: disassemble-lib disassemble-main

disassemble-lib: lab0x06-Problem2-lib-original
	objdump -D lab0x06-Problem2-lib-original.o -M intel > lab0x06-Problem2-lib-original.dump
	gcc -m32 -S lab0x06-Problem2-lib-original.c -masm=intel
disassemble-main: lab0x06-Problem2-main.c
	gcc -m32 -S lab0x06-Problem2-main.c -masm=intel

# ------ BUILD Program 1 ------

# Build asm
lab0x06-HackMe:  lab0x06-HackMe.asm
	nasm -f elf -g -F dwarf  lab0x06-HackMe.asm
	ld -m elf_i386  lab0x06-HackMe.o -o  lab0x06-HackMe -lc -I /lib/ld-linux.so.2

# Build input
lab0x06-HackInput: input
	mv input.txt lab0x06-HackInput.txt

input: input.txt
	perl -e 'print "13", "\xec\x82\x04\x08" x 9;' > input.txt

input2: input.txt
	perl -e 'print "13", " ", "A" x <STDIN>, "\n", "\0";' > input.txt

input3: input.txt
	perl -e 'print "13", "\xec\x82\x04\x08" x <STDIN>;' > input.txt

input4: input.txt
	perl -e 'print "13", "\xec\x82\x04\x08" x <STDIN>, "\xd8\x96\xea\xf7";' > input.txt
	
# ------ END Program 1 ------


# ------ BUILD Program 2 ------

# Build main
lab0x06-Problem2-main: lab0x06-Problem2-main.c lab0x06-Problem2-lib-original
	gcc -g -m32 -o lab0x06-Problem2-main lab0x06-Problem2-lib-original.o lab0x06-Problem2-main.c

lab0x06-Problem2-main-modified: lab0x06-Problem2-main.c lab0x06-Problem2-lib-modified
	gcc -g -m32 -o lab0x06-Problem2-main lab0x06-Problem2-lib-modified.o lab0x06-Problem2-main.c


# Build library
lab0x06-Problem2-lib-original: lab0x06-Problem2-lib-original.c
	gcc -g -m32 -c lab0x06-Problem2-lib-original.c

lab0x06-Problem2-lib-modified: lab0x06-Problem2-lib-modified.asm
	nasm -f elf -g -F dwarf  lab0x06-Problem2-lib-modified.asm
# ------ END Program 2 ------

clean:
	rm  lab0x06-HackMe lab0x06-Problem2-main *.o -f
