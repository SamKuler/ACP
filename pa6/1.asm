include msvcrt.inc
includelib msvcrt.lib

.386
.model flat, stdcall
option dotname

.data
    formatOutput BYTE "Address %08X = %08X", 10, 0

.code

printf  PROTO C :PTR BYTE, :VARARG

ShowParams PROC USES eax ebx ecx edx,
    paramCount:DWORD
    
    LOCAL paramAddress:DWORD
    
    ; EBP + 8 是 ShowParams 的第一个参数 paramCount
    ; EBP + 4 是返回地址
    ; EBP + 0 是保存的 EBP
    
    mov ebx, [ebp]               ; 获取调用者的 EBP
    add ebx, 8                      ; 指向调用者的第一个参数
    mov paramAddress, ebx
    
    mov ecx, paramCount         ; 循环计数器
    
DisplayLoop:
    push ecx
    ; 显示地址
    mov ebx, paramAddress
    mov eax, [ebx]
    invoke printf, addr formatOutput, paramAddress, eax

    pop ecx
    
    ; 移动到下一个参数
    add paramAddress, 4
    loop DisplayLoop
    
    ret
ShowParams ENDP

MySample PROC first:DWORD, second:DWORD, third:DWORD
    
    LOCAL paramCount:DWORD
    mov paramCount, 3
    invoke ShowParams, paramCount
    ret
MySample ENDP

main PROC
    invoke MySample, 1234h, 5000h, 6543h    ; Params in Stack
    ret
main ENDP

END main