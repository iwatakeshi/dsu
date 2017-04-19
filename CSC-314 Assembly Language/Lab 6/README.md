Lab 6 Problem 1
================

The idea behind hacking in this lab is to manipulate the ebp, esp, eip registers.
At first, the task of hacking seemed daunting but after reading first few chapters of Hacking: The Art of Exploitation, bits of information started to come together. 

I started to annotate the asm file by marking the changes in ebp and esp to see what their addresses were.
The annotated file can be found in the same directory under **lab0x06-HackMe.annotated.asm**. Through annotation and the use of gdb, I was able to see the effect of buffer overflow when an input goes "past its limit" (segmentation fault). 
The book explains that "[a]s long as the start of the buffer is aligned  with DWORDs on the stack, this mutability can be accounted for by simply repeating the return address many times." 

To be honest, I wasn't sure whether the lab had it in this format, but by using gdb, it did show that the ebp register was overwritten with the input garbage that I had created. So I created a simple make script that allowed me to generate an input file with the return address by the number of times it should repeat. The makefile is also available in the same directory with a rule named **lab0x06-HackInput**. After some trial and error, I found out that the number of times to fill the input with the return address was 9. With this input, I was able to hack my way to the _NullZone.

There are images that show the ebp, esp, and eip registers at certain breakpoints. Please see these images as they show the work done for this lab. Note that the last image actually shows ebp pointing to the _NullZone.


Lab 6 Problem 2
=================

I have successfully optimized the library. The images for before and after are
**lab6p2-02.png** and **lab6p2-08.png** respectively. There are located under
**lab0x06-images/**.