section .bss 
 
   decimalBuf resb 12 
 
section .text                   ;section declaration 
 
                                ;we must export the entry point to the ELF linker or 
    global  _start              ;loader. They conventionally recognize _start as their 
                    ;entry point. Use ld -e foo to override the default. 
 
 
_start: 
 
    ; set up for calling the conversion routine 
    mov ebx, decimalBuf 
    mov eax, 0xff09             ; put a number here to convert to decimal 
                                ; you can use this program to convert hex to decimal! 
    call _PosIntToDecStr        ; call the conversion routine 
                                ; execution jumps to the instruction at _PosIntToDecStr 
                                ; from there, ret will jump back to the next instr after this 
 
    ;write our decimal string to stdout 
    mov     edx,ecx             ; our routine comes back with digit count in ecx -> move to edx for sys_write 
    mov     ecx,ebx             ; ebx points to first decimal digit, but sys_write wants pointer in ecx, so move it 
    mov     ebx,1               ;first argument: file handle (stdout) 
    mov     eax,4               ;system call number (sys_write) 
    int     0x80                ;call kernel 
 
                                
_exit: 
    mov     ebx,0               ;first syscall argument: exit code 
    mov     eax,1               ;system call number (sys_exit) 
    int     0x80                ;call kernel 
 
_PosIntToDecStr: 
    ; convert an unsigned 32bit integer in eax to a string of decimal digits 
    ; the string will be stored in buffer pointed to by ebx 
    ; ecx will store the count of decimal digits 
 
    ; eax -- the integer (an unsigned integer) 
    ; ebx -- pointer to string buffer (assumed to be at least 12 bytes!!) 
    ; ecx -- counter of decimal digits 
    ; ebp -- store our divisor: 10   
 
    ; note because we work backwards from low to high digit we fill in from 
    ; the 12 byte in buffer and return pointer to first character of the 
    ; decimal version, which likely will not be the first byte of the buffer 
    ; calling code needs to keep track of it's original buffer pointer 
 
    asciiZero equ 0x30          ; define symbol for ascii code of zero 
                                ; moved it here so if we copy/paste it goes together 
 
 
    add ebx,11           ; point to 12th byte of buffer (we will fill the digits in "backwards") 
 
    mov byte [ebx],0x0a  ; lets put a newline character here to make printing easier 
                         ; now we are not guaranteeing a valid string 
                         ; maybe we should really just let the calling code deal 
                         ; with whether it wants a newline or null or both or neither 
                         ; it really should not be the job of this subroutine! 
                          
                          
    mov ecx, 1         ; ecx will count our digits, make sure it starts at zero 
                       ; starting at 1 to include the newline character 
_PosIntToDecStr_Loop: 
 
    dec ebx           ; decrement ebx to point to byte position of last decimal digit 
 
    ; is there an improvement to efficiency we can make here, related to this instruction?  why or why not? 
    mov ebp,10        ; we will be dividing by 10, keep it here… 
                      ; using ebp to store divisor, to avoid collision with esi&edi used by fibonacci program 
 
    mov edx,0x0000    ; the dividend is edx:eax, so we put 0's in high bits in edx 
    div ebp           ; will calculate eax / ebp 
                      ;    quotient --> eax 
                      ;    remainder --> edx 
 
    add edx,asciiZero ; add ascii code of '0' to remainder(which is put in edx by div command) 
                      ; conveniently, this gives ascii code of the digit,  
                      ;    because the ascii codes of digits are in order 0x30...0x39 
 
    mov [ebx], dl     ; store the digit into its position in the buffer 
                      ; the dl register is the least significant byte of the ecx register 
                      ; there is also dh, the second lowest byte of edx 
                      ; and dx is the lower two bytes of edx (so dx is dh:dl) 
                      ; these are literall parts of the same register, so changing dl would chance edx 
 
    inc ecx           ; increment our digit counter 
 
    ;can these two instructions be simplified to one instruction? why or why not? 
          cmp eax, 0                   ; check if eax is zero... 
    jne _PosIntToDecStr_Loop     ; if it was NOT a zero, the loop back for next digit 
 
    ret               ; return -- note that ebx now points to first (most significant) digit of decimal string 
 
section .data                   ;section declaration 
 
msg db      "Go away! I refuse to say 'hello', world!",0xa ;our dear string 
len equ     $ - msg             ;length of our dear string 
