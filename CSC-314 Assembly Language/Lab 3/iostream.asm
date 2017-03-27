%ifndef iostream_h
%define iostream_h

%include "string.asm"

section .data
  sys_read equ 3
  sys_write equ 4
  fd_stdin equ 0
  fd_stdout equ 1

%define buffer_size 100000

section .text

  global cout, cin
  
  ; print - prints a string to the console
  ; @param ecx - A string to print
  ; @param edx - The string length
  print:
    mov eax, sys_write
    mov ebx, fd_stdout
    int 80h
    ret
  ; cin - reads a string from the console
  ; @param ecx - An string buffer to store the input
  ; @param edx - The buffer length
  read:
    mov ebx, fd_stdin
    mov eax, sys_read
    int 80h
    ret
  ; cout - prints a string to the console
  ; @param eax - a string to print
  cout:
    push edx
    push ecx
    push ebx
    push eax
    call slen
 
    mov edx, eax
    pop eax
 
    mov ecx, eax
    mov ebx, fd_stdout
    mov eax, sys_write
    int 80h
 
    pop ebx
    pop ecx
    pop edx
    ret


  ; cin - reads a string from the console
  ; @param eax - The destination buffer
  ; @return - The string buffer
  cin:
    mov edi, eax
    push edx
    push ecx
    push ebx
    mov eax, sys_read
    mov ebx, fd_stdin
    mov ecx, edi           ; buffer
    mov edx, buffer_size   ; read byte count
    int 80h                ; interrupt
    pop ebx
    pop ecx
    pop edx
    ret

    cout.clear:   
    mov 	edx, 1
    mov 	ecx, 1            ; dummy buffer
    mov 	ebx, fd_stdin
    mov 	eax, sys_read
    int 	80h 	
    cmp		byte [ecx + edx - 1], 10
    jne 	cout.clear
    ret


%endif
