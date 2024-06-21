/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:19:47 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/19 16:19:51 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* This function returns the point where the keyword starts if the heredoc 
sign "<<" is valid */
int	wheredoc(char *str, int i)
{
	while (str[i])
	{
		while (str[i] != '<')
			i++;
		if (!str[i] || !str[i + 1] || !str[i + 2])
			return (-1);
		if (str[i + 1] != '<')
		{
			i++;
			continue;
		}
		else if (str[i + 2] == '<')
			return -1;
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && check_chr(str[i]))
			break;
		else
			return (-1);
	}
	return (i);
}

/* This function parses and saves the heredoc keyword, trims the quotes if
it finds them and manage the token token to expand. */
char	*keyword_hd(t_fd *new, char *in, int *i, char q)
{
	char	*str;
	int		j;

	j = 0;
	while (in[j] && in[j + 1] && check_chr(in[0]) != 2
		&& check_chr(in[j + 1]) != 2 && check_chr(in[j + 1]))
		j++;
	if (check_chr(in[0]) == 2)
		j = word_in_quotes(in, &q, -1);
	while (in[j] && in[j + 1] && check_chr(in[j + 1]) == 2)
		j = word_in_quotes(in, &q, j);
	str = ft_substr(in, 0, j + 1);
	 if (str)
	 	str = trim_quotes(str, ' ', ft_strlen(str), -1);
	if (!str)
		return (NULL);
	if (q == '\'' || q == '\"')
		new->token = HEREDOC_NO_EXP;
	*i += j;
	return (str);
}

/* 
This function creates a pipe to save the heredoc content in it.
The pipe is used as a buffer with a file descriptor to read from. 
Then it opens a readline, we can fill it from standart input.
It compares each line with the key word and if it's not the keyword 
it saves the line in the buffer. 
1. return (-1) - if pipe() error occures
2. return (fd) - a file descriptor to read the content of the heredoc
*/
/*int	save_hd(t_toolkit *tool, char *key, char *str, int token)
{
	int	hd[2];

	if (pipe(hd) < 0)
		return (-1);
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (hd_close(hd, 0));
		else if (!ft_strncmp(str, key, ft_longer(str, key)) && \
				(ft_strncmp(str, "\n", 1)))
			break ;
		else if (!ft_strncmp(str, "\n", 1) && (*key == '\0'))
			break ;
		str = expand_hd(tool, str, token);
		if (!str)
			return (hd_close(hd, 1));
		write(hd[1], str, ft_strlen(str));
		write(hd[1], "\n", 1);
		str = ft_memdel(str);
	}
	str = ft_memdel(str);
	close(hd[1]);
	return (hd[0]);
}*/

int	save_hd(t_toolkit *tool, char *key, char *str, int token)
{
	int	hd[2];

	if (pipe(hd) < 0) {
		printf("Debug: Failed to create pipe.\n");
		return (-1);
	}
	while (1)
	{
		str = readline("> ");
		printf("Debug: Readline input: %s\n", str);

		if (!str) {
			printf("Debug: Readline returned NULL.\n");
			return (hd_close(hd, 0));
		} else if (!ft_strncmp(str, key, ft_longer(str, key)) && \
				(ft_strncmp(str, "\n", 1))) {
			printf("Debug: Input matches key and is not a newline.\n");
			break;
		} else if (!ft_strncmp(str, "\n", 1) && (*key == '\0')) {
			printf("Debug: Input is a newline and key is empty.\n");
			break;
		}

		str = expand_hd(tool, str, token);
		if (!str) {
			printf("Debug: Expansion returned NULL.\n");
			return (hd_close(hd, 1));
		}

		write(hd[1], str, ft_strlen(str));
		write(hd[1], "\n", 1);
		printf("Debug: Written to pipe: %s\n", str);

		str = ft_memdel(str);
	}

	str = ft_memdel(str);
	close(hd[1]);
	printf("Debug: Pipe write end closed.\n");

	return (hd[0]);
}

int	hd_close(int fd[], int flag)
{
	close(fd[1]);
	if (flag)
	{
		close(fd[0]);
		return (-12);
	}
	return (fd[0]);
}

/* This fuction checks whether there are heredocs, sets the point where
it starts and saves its information in a fd_node */
/*int	heredoc(t_toolkit *tool, char *input, int i)
{
	t_fd	*new;

	if (!ft_strnstr(input, "<<", ft_strlen(input)))
		return (0);
	while (input[i])
	{
		i = wheredoc(input, 0);
		if (i <= 0)
			return (0);
		input = input + i;
		new = malloc(sizeof(t_fd));
		if (!new)
			return (err_break(tool, "heredoc", NULL, 12));
		new->next = NULL;
		new->token = HEREDOC;
		fd_add(&(tool->hd_lst), new);
		new->str = keyword_hd(new, input, &i, ' ');
		if (!new->str)
			return (err_break(tool, "heredoc", NULL, 12));
		new->fd = save_hd(tool, new->str, NULL, new->token);
		if (new->fd < 0)
			return (err_break(tool, "heredoc",  NULL, -(new->fd)));
		i = 0;
	}
	return (0);
}*/
int	heredoc(t_toolkit *tool, char *input, int i)
{
	t_fd	*new;

	if (!ft_strnstr(input, "<<", ft_strlen(input))) {
		printf("Debug: No heredoc found in input.\n");
		return (0);
	}
	i = wheredoc(input, 0);
	while (input[i])
	{
		printf("Debug: wheredoc returned index: %d\n", i);

		if (i <= 0) {
			printf("Debug: Invalid index returned by wheredoc.\n");
			return (0);
		}

		input = input + i;
		printf("Debug: Updated input: %s\n", input);

		new = malloc(sizeof(t_fd));
		if (!new) {
			printf("Debug: Memory allocation failed for new t_fd.\n");
			return (err_break(tool, "heredoc", NULL, 12));
		}

		new->next = NULL;
		new->token = HEREDOC;
		fd_add(&(tool->hd_lst), new);
		printf("Debug: Added new t_fd to hd_lst.\n");

		new->str = keyword_hd(new, input, &i, ' ');
		printf("Debug: keyword_hd returned: %s\n", new->str);

		if (!new->str) {
			printf("Debug: keyword_hd returned NULL.\n");
			return (err_break(tool, "heredoc", NULL, 12));
		}

		new->fd = save_hd(tool, new->str, NULL, new->token);
		printf("Debug: save_hd returned fd: %d\n", new->fd);

		if (new->fd < 0) {
			printf("Debug: save_hd failed with fd: %d\n", new->fd);
			return (err_break(tool, "heredoc",  NULL, -(new->fd)));
		}

		i = 0;
	}

	printf("Debug: Heredoc processing completed.\n");
	return (0);
}
