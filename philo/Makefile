NAME = philo
# ARCHIVE = push_swap.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
# MAKE_LIB = ar -rcs

# INC = -Iincludes/ -Ilibft/ -Iprintf/

LIBS = -lpthread

SRCS = philo.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : 
	$(CC) $(SRCS) $(LIBS) -o $@

test:
	$(CC) tests.c $(SRCS) $(LIBS) -g -o $@

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
	
clean :
	rm -rf $(OBJS) *.dSYM a.out *.o

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re