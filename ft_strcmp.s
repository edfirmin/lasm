section .text
    global ft_strcmp

ft_strcmp:
    xor rax, rax
    xor rcx, rcx

.loop:
    movzx rax, byte [rdi]
    movzx rcx, byte [rsi]
    sub rax, rcx
    jne .return
    cmp byte [rdi], 0
    je .return
    inc rdi
    inc rsi
    jmp .loop

.return:
    ret
