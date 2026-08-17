NAME    = libasm.a

OBJS    = $(SRCS:.s=.o)

NASM    = nasm

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

NASMFLAGS = -f elf64

AR      = ar
ARFLAGS = rcs

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.s
	nasm -f macho64 $< -o $@

# Compile a main.c against the library
# Usage: make test
test: $(NAME)
	$(CC) $(CFLAGS) -arch x86_64 main.c -L. -lasm -o test_libasm
	./test_libasm

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) test_libasm

re: fclean all