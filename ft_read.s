extern __errno_location

global ft_read

section .text

ft_read:
    mov rax, 0
    syscall
    cmp rax, 0
    jl  .error
    ret

.error:
    neg rax
    push rax
    call __errno_location
    pop rdx
    mov [rax], edx
    mov rax, -1
    ret