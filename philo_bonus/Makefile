# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rthammat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 18:15:31 by rthammat          #+#    #+#              #
#    Updated: 2022/12/24 21:12:56 by rthammat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -g

SRCS = philo_bonus.c \
	utils.c \
	init.c \
	time.c \
	check_dead.c \
	routine.c \
	clear.c \
	process.c \

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
