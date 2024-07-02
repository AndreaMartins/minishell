# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 17:17:13 by mmarsa-s          #+#    #+#              #
#    Updated: 2024/07/02 12:49:43 by andmart2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = includes/minishell.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g \
         -I/usr/local/opt/readline/include \
         -Iincludes -fsanitize=address

OBJ = $(SRC:.c=.o)
LIBFT = ./includes/libft/libft.a
MAKE_LIBFT = make -C includes/libft --no-print-directory

READLINE = -L/usr/local/opt/readline/lib \
           -lreadline -lhistory -ltermcap

MAIN = src/main.c src/shell_init.c

LEXER = src/lexer/syntax.c src/lexer/fd_utils.c src/lexer/heredoc.c \
        src/lexer/lexer.c src/lexer/t_lex_lst.c src/lexer/tools.c \
        src/lexer/utils.c

EXPANSER = src/expanser/expanser.c src/expanser/expanser_utils.c \
           src/expanser/expanser_structure.c

PARSER = src/parser/parser.c src/parser/parser_utils.c

EXECUTOR = src/executor/executor.c src/executor/executor_utils.c

ERRORS = src/errors/errors.c

BUILTINS = src/builtins/cd.c src/builtins/echo.c src/builtins/env.c \
           src/builtins/exit.c src/builtins/export_utils.c \
           src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c

ENV = src/env/env_free.c src/env/env_list.c src/env/env_sort.c \
      src/env/env_utils.c src/env/env.c

SIGNALS = src/signals/signals.c

SRC = $(MAIN) $(LEXER) $(ERRORS) $(EXPANSER) $(PARSER) $(EXECUTOR) \
      $(SIGNALS) $(BUILTINS) $(ENV)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C includes/libft clean --no-print-directory
	rm -f $(LIBFT)
	rm -f $(NAME)

fclean: clean
	$(MAKE) -C includes/libft fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re



