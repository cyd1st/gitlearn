; 注释：分号开始
section .data           ; 数据段
    msg db 'Hello, World!', 0xA  ; db = define byte, 0xA = 换行
    len equ $ - msg     ; $ = 当前位置，计算字符串长度

section .text           ; 代码段
    global _start       ; 入口点标记

_start:
    ; 系统调用：write(文件描述符, 字符串地址, 长度)
    mov rax, 1          ; 系统调用号1 = write
    mov rdi, 1          ; 文件描述符1 = 标准输出
    mov rsi, msg        ; 字符串地址
    mov rdx, len        ; 字符串长度
    syscall             ; 触发系统调用

    ; 系统调用：exit(退出码)
    mov rax, 60         ; 系统调用号60 = exit
    mov rdi, 0          ; 退出码0 = 成功
    syscall