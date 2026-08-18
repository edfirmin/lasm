section .text
    global ft_strcpy
	
ft_strcpy:
    push rdi
.loop:
    cmp byte [rsi], 0x00
    jz .return
    movsb
    jmp .loop
.return:
    mov byte [rdi], 0
    pop rax
    ret
