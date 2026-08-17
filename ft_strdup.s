extern _ft_strlen
extern _malloc
extern _ft_strcpy

section .text
	global _ft_strdup
	_ft_strdup:
		push rdi
		call _ft_strlen
		mov rdi, rax
		inc rdi
		call _malloc
		pop rsi
		push rax
		mov rdi, rax
		call _ft_strcpy
		pop rax
		ret
