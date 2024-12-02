CC=gcc
FLAGS=-Wall -Werror -Wextra
NAME = libft.a

LIST = ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isalnum.c ft_atoi.c ft_bzero.c ft_calloc.c ft_strdup.c ft_itoa.c ft_atol.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_strlcpy.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OBJ = $(patsubst %.c,%.o,$(LIST))

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $?

%.o: %.c
	$(CC) $(FLAGS) -g -c $< -o $@

part1: test1 $(NAME)
	$(CC) $(FLAGS) -g test1.c libft.a -o part1 -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -lbsd
	./part1

part2: test2 $(NAME)
	$(CC) $(FLAGS) -g test2.c libft.a -o part2 -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -lbsd
	./part2

test1:
	checkmk clean_mode=1 part1.check > test1.c

test2:
	checkmk clean_mode=1 part2.check > test2.c

clean:
	rm -f $(OBJ) part2 part1 test1.c test2.c libft.a

fclean: clean
	rm -f $(NAME)

re: fclean all

git:
	git add Makefile *.c libft.h
	git commit
	git push origin master

.PHONY: all clean fclean re git

