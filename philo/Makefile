NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread 

LIBS = -lpthread

SRCS = tests.c philo.c ../libft/libft.a
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : libs
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $@

test: libs
	$(CC) -fsanitize=address tests.c philo.c ../libft/libft.a -lpthread -g -o test

libs:
	cd ../libft && $(MAKE)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
	
clean :
	rm -rf $(OBJS) *.dSYM a.out *.o test; cd ../libft; make clean

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re

# RELINKING