include msvcrt.inc
includelib msvcrt.lib

.386
.model flat, stdcall
option dotname

printf  PROTO C :PTR BYTE, :VARARG
scanf   PROTO C :PTR BYTE, :VARARG
malloc  PROTO C :DWORD
free    PROTO C :PTR

.data
	arrayBuffer DWORD ?
	N DWORD 0

	formatSingleNumberInput BYTE "%hd", 0
	formatSingleNumberOutput BYTE "%hd ", 0
    formatNInput BYTE "%d", 0

.code

bubbleSort PROC USES ebx esi edi,
    arrayPtr:DWORD,
    arraySize:DWORD
    
    mov esi, arrayPtr
    mov edi, arraySize
    dec edi
    
    cmp edi, 0
    jle .done
    
.outer:
    xor edx, edx        ; 交换标志
    xor ebx, ebx        ; j = 0
    
.inner:
    mov ax, [esi + ebx*2]
    mov cx, [esi + ebx*2 + 2]
    cmp al, cl
    jbe .skip
    
    mov [esi + ebx*2], cx
    mov [esi + ebx*2 + 2], ax
    inc edx
    
.skip:
    inc ebx
    cmp ebx, edi
    jl .inner
    
    test edx, edx
    jz .done
    dec edi
    jnz .outer
    
.done:
    ret
bubbleSort ENDP


main PROC
	invoke scanf, ADDR formatNInput, ADDR N

    mov eax, N
    shl eax, 1          ; 乘以 2，计算所需字节数
	invoke malloc, eax
	test eax, eax
	jz .exit_main
	
	mov arrayBuffer, eax

	; 读取 N 个整数到数组
	mov ecx, N
.loop1:
    push ecx                ; 保存 ECX
    neg ecx
    add ecx, N
    
    mov edx, arrayBuffer    ; EDX = 数组基址
    lea edx, [edx + ecx*2]  ; EDX = arrayBuffer + ecx * 2
    
    invoke scanf, ADDR formatSingleNumberInput, edx
    
    pop ecx                 ; 恢复 ECX
    loop .loop1

	; 排序数组
	invoke bubbleSort, arrayBuffer, N

	; 输出排序后的数组
	mov ecx, N
.loop2:
	push ecx                ; 保存 ECX
    neg ecx
    add ecx, N
    
    mov edx, arrayBuffer
    movzx edx, WORD PTR [edx + ecx*2]    ; 防止符号扩展
    invoke printf, ADDR formatSingleNumberOutput, edx
    pop ecx                 ; 恢复 ECX
    loop .loop2

	invoke free, arrayBuffer

.exit_main:
	ret

main ENDP

END main