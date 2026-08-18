NAME = libasm.a

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

OBJS = $(SRCS:.s=.o)

ASMFLAGS = -f elf64

RM = rm -f

CC = gcc

all: $(NAME)

%.o: %.s
	nasm $(ASMFLAGS) $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) test_exe

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME) main.c
	$(CC) -Wall -Wextra -Werror main.c -L. -lasm -o test_exe
	./test_exe

.PHONY: all clean fclean re test