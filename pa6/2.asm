include msvcrt.inc
includelib msvcrt.lib

.386
.model flat, stdcall

printf PROTO C :DWORD, :VARARG

.data
    targetStr BYTE "ABCDE", 10 DUP(0)
    sourceStr BYTE "FGH", 0
    formatRaw BYTE "%s", 10, 0

.code
Str_concat PROC USES esi edi eax,
    targetPtr:DWORD,
    sourcePtr:DWORD
    
    cld                     ; 方向向前
    
    ; 目标字符串的末尾（使用 SCASB）
    mov edi, targetPtr
    mov ecx, 0FFFFFFFFh     ; 最大搜索长度
    xor al, al                         ; AL = 0
    repne scasb                    ; 扫描直到找到 '\0'
    dec edi                          ; 回退到 '\0' 的位置
    
    ; 计算源字符串长度（包括 '\0'）
    mov esi, sourcePtr
    push edi                     ; 保存目标位置
    mov edi, esi                ; 临时用 EDI 扫描源字符串
    mov ecx, 0FFFFFFFFh  ; 最大搜索长度
    repne scasb                 ; 找到源字符串的 '\0'
    not ecx                        ; ECX = 长度 + 1（包括 '\0'）
    pop edi                        ; 恢复目标位置
    
    ; 复制（包括 '\0'）
    mov esi, sourcePtr
    rep movsb               ; 复制 ECX 个字节
    ret

Str_concat ENDP

main PROC
    ; 输出源字符串
    invoke printf, ADDR formatRaw, ADDR sourceStr
    
    ; 输出目标字符串
    invoke printf, ADDR formatRaw, ADDR targetStr
    
    ; 执行字符串连接
    invoke Str_concat, ADDR targetStr, ADDR sourceStr
    
    ; 输出连接后的结果
    invoke printf, ADDR formatRaw, ADDR targetStr
    
    xor eax,eax
    ret

main ENDP

END main