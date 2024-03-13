/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:40:49 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/12 16:40:51 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef struct s_envlst
{
	char				*key;
	char				*val;
	struct s_envlst		*next;
}	t_env;

typedef enum s_tokens
{
	SPACE = 0,
	STR,
	DOUBLEQ,
	SIMPLEQ,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_exp
{
	char	*cont;
	char	*new;
	char	*var;
	char	*val;
	int		alloc;
	int		k;
	int		j;
	int		fl;
	char	q;
}	t_exp;

typedef struct s_fd
{
	int			fd;
	int			type;
	int			exp;
	char		*str;
	struct s_fd	*next;
}	t_fd;

typedef struct s_pipe
{
	char			**cmd;
	char			*path;
	t_fd			*fd_lst;
	int				in_fd;
	int				out_fd;
	int				builtin;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_exec
{
	int		fdp[2];
	int		pid;
	int		stat;
}	t_exec;

typedef struct s_toolkit
{
	t_env	*env_lst;
	t_lexer	*lex_lst;
	t_pipe	*pipe_lst;
	t_fd	*hd_lst;
	t_exp	*exp;
	char	*args;
	char	**paths;
	int		exit;
	int		pipes;
	int		check;
	t_exec	*exe;
	char	**env;
	int		power_on;
}	t_toolkit;


int	main(int argc, char **argv, char **envp);

#endif