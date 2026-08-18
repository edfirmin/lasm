section .text
    global ft_strlen

ft_strlen:
    xor rax, rax
    cmp byte [rdi], 0x00
    jne .loop
    ret

.loop:
    inc rdi
    inc rax
    cmp byte [rdi], 0x00
    jne .loop
    ret