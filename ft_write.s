extern ___error

global _ft_write

section .text           ; Directives d'instructions exécutables

_ft_write:
    mov rax, 0x2000004  ; Syscall write macOS x86_64
    syscall
    jc  .error          ; Si Carry Flag = 1, saut vers l'erreur
    ret

.error:
    push rax            ; Sauvegarde du code d'erreur
    call ___error       ; RAX pointe sur errno
    pop rdx
    mov [rax], edx      ; *errno = code_erreur
    mov rax, -1         ; Retourne -1
    ret
