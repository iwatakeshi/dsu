# Lab 5

Lab0x05-grep: Lab0x05-grep.asm grep.o
	nasm -f elf -g -F dwarf Lab0x05-grep.asm
	g++ -m32 -g Lab0x05-grep.o grep.o -o Lab0x05-grep

grep.o: grep.cpp
	g++ -m32 -g grep.cpp -c

clean:
	rm Lab0x05 main Lab0x05-grep *.o -f
