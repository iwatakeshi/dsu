section .bss
    userNumber resb 4
    
section .text

    GLOBAL _start
    
_start:

    EXTERN  _PrintNumber
    EXTERN  _ReadNumber
    
    mov ebp, esp         ; save the initial stack pointer to EBP
                         ; this way we know where the top of the stack is

     
_PushLoop:

    mov esi, userNumber 
    call _ReadNumber      ; read a number from user, 
                          ; the converted binary integer will be stored at location pointed to by ESI
 
    cmp dword [userNumber], 0
    je _PopLoop
    push dword [userNumber]    ; subtract 4 from ESP, copy 4 bytes from [userNumber] 
                               ; to the top 4 bytes of the stack
    jmp _PushLoop
    
    ;mov eax, [userNumber]
    ;cmp eax, 0
    ;je _PopLoop
    ;push eax
    ;jmp _PushLoop
    
_PopLoop:

    pop eax      ; get top 4 bytes from stack into EAX, add 4 to ESP
    call _PrintNumber
    
    cmp esp, ebp
    jne _PopLoop
    
_TryCallAndReturn:

    call _someSubRoutine    
    
    
_exit:
    mov     ebx,0               ;first syscall argument: exit code
    mov     eax,1               ;system call number (sys_exit)
    int     0x80                ;call kernel    
    
    
_someSubRoutine: ; a subroutine that does nothing...

    ;sub esp, 12
    ret
    
