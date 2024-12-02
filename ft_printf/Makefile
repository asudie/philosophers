CC=gcc
FLAGS=#-Wall -Werror -Wextra
NAME = libftprintf.a

LIST = ft_printf.c utils.c

OBJ = $(patsubst %.c,%.o,$(LIST))

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $?

%.o: %.c
	$(CC) $(FLAGS) -g -c $< -o $@

run: test $(NAME)
	$(CC) $(FLAGS) -g test.c libftprintf.a -o ft_printf -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
	./ft_printf

test:
	checkmk clean_mode=1 test.check > test.c

clean:
	rm -f $(OBJ) ft_printf test.c debug.c a.out *.o *.a

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	gcc -g debug.c ft_printf.c utils.c

git:
	git add Makefile ft_printf.c ft_printf.h utils.c
	git commit
	git push origin master

.PHONY: all clean fclean re git
