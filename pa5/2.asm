.386
.model flat, stdcall
option casemap:none

include msvcrt.inc
includelib msvcrt.lib

.data
    vala dword 0h
    valb sword 0h
    valc byte 0h
    format db "%d %d %d", 0

.code
main PROC
    mov eax, sizeof vala
    mov ebx, sizeof valb
    mov ecx, sizeof valc
    
    invoke crt_printf, addr format, eax, ebx, ecx

    ret
main ENDP
END main