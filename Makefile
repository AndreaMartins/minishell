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

CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(HOME)/.brew/Cellar/readline/8.2.10/include

OBJ = $(SRC:.c=.o)
LIBFT = ./includes/libft/libft.a
MAKE_LIBFT = make -C includes/libft --no-print-directory
READLINE = -L$(HOME)/.brew/Cellar/readline/8.2.10/lib -lreadline -lhistory

MAIN = src/main.c src/shell_init.c

LEXER = src/lexer/syntax.c src/lexer/fd_utils.c src/lexer/heredoc.c \
		src/lexer/lexer.c src/lexer/t_lex_lst.c src/lexer/tools.c

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
