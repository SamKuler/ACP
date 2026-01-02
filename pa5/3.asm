.386
.model flat, stdcall
option casemap:none

include msvcrt.inc
includelib msvcrt.lib

.data
    myArray WORD 20 DUP(?)
    format db "%d", 0

.code
main PROC
    mov eax, sizeof myArray
    
    invoke crt_printf, addr format, eax

    ret
main ENDP
END main