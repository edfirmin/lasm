extern ft_strlen
extern malloc
extern ft_strcpy

section .text
    global ft_strdup

ft_strdup:
    push rdi
    call ft_strlen
    mov rdi, rax
    inc rdi
    call malloc
    cmp rax, 0
    je .error
    pop rsi
    push rax
    mov rdi, rax
    call ft_strcpy
    pop rax
    ret

.error:
    pop rsi
    mov rax, 0
    ret
