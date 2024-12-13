NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread
LIBS = -lpthread

SRCS = tests.c philo.c monitor.c create_philos.c routine.c utils.c
OBJS = $(SRCS:.c=.o)
LIBFT = ../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	cd ../libft && $(MAKE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJS) $(LIBFT)
	$(CC) -fsanitize=address $(OBJS) $(LIBFT) $(LIBS) -g -o test

clean:
	rm -rf $(OBJS) *.dSYM a.out *.o test; cd ../libft && make clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libs test
