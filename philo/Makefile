NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -g

SRCS = philo.c \
	ft_atoi.c \
	init.c \
	time.c \
	create_and_join.c \
	utils.c \
	action.c \
	clear.c \

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

norminette:
	norminette -R CheckForbiddenHeader *.h *.c

clean:
	rm -rf *.dSYM $(NAME)

fclean: clean

re : fclean all

.PHONY: clean fclean re norminette
