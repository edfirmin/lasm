section .text
    global _ft_strcmp

_ft_strcmp:
    xor rax, rax        ; Réinitialise rax à 0
    xor rcx, rcx        ; Réinitialise rcx à 0

.loop:
    movzx rax, byte [rdi] ; Charge l'octet en UNSIGNED (0 à 255)
    movzx rcx, byte [rsi] ; Charge l'octet en UNSIGNED (0 à 255)

    sub rax, rcx          ; Calcule la différence (rax - rcx)
    jne .return           ; Si les caractères sont différents, termine

    cmp byte [rdi], 0     ; Si fin de chaîne 1 ('\0')
    je .return

    inc rdi
    inc rsi
    jmp .loop

.return:
    ret
