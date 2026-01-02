.386
.model flat, stdcall
option casemap:none

include msvcrt.inc
includelib msvcrt.lib

.data
    varA dword 5
    varB dword 6
    sum DWORD 0
    product DWORD 0
    format db "%d %d", 0

.code
main PROC
    ; varA + varB
    mov eax, varA
    add eax, varB
    mov sum, eax
    
    ; varA * varB
    mov eax, varA
    imul eax, varB
    mov product, eax
    
    ; print
    invoke crt_printf, addr format, sum, product

    ret
main ENDP
END main