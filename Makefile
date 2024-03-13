# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 17:17:13 by mmarsa-s          #+#    #+#              #
#    Updated: 2024/03/12 17:17:16 by mmarsa-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = includes/minishell.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c
OBJ = $(SRC:.c=.o)
LIBFT = ./includes/libft/libft.a
MAKE_LIBFT = make -C includes/libft --no-print-directory
READLINE = -L/Users/mmarsa-s/.brew/Cellar/readline/8.2.10/lib -lreadline

all: make_lib $(NAME)

make_lib:
	$(MAKE_LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C includes/libft fclean --no-print-directory

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean make_lib
