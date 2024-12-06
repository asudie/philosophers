NAME = philo
# ARCHIVE = push_swap.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread 
# MAKE_LIB = ar -rcs

#  INC = -Iincludes/ -Ilibft/

LIBS = -lpthread

SRCS = philo.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : 
	$(CC) $(SRCS) $(LIBS) -o $@

test: libs
	$(CC) -fsanitize=address -g -L../libft -lft tests.c $(SRCS) $(LIBS) -o $@

libs:
	cd ../libft && $(MAKE)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
	
clean :
	rm -rf $(OBJS) *.dSYM a.out *.o test

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re