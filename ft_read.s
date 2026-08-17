extern ___error

global _ft_read

section .text           ; <-- A ajouter juste avant le début du code

_ft_read:
    mov rax, 0x2000003  ; Syscall read macOS
    syscall
    jc  .error
    ret

.error:
    push rax
    call ___error
    pop rdx
    mov [rax], edx
    mov rax, -1
    ret