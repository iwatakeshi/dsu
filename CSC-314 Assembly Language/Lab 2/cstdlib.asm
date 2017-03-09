%ifndef cstdlib_h
%define cstdlib_h
%define sys_exit 1
global exit

exit:
    mov ebx, 0
    mov eax, sys_exit
    int 80h
    ret

%endif