/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:30:06 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/16 15:25:50 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_builtin(char **cmd)
{
    if (!cmd || !(*cmd))
    {
        printf("cmd is NULL or cmd[0] is NULL\n");
        return 0;
    }
    
    printf("cmd[0]: %s\n", cmd[0]);

    int echo_len = ft_longer(cmd[0], "echo");
    printf("Length of 'echo': %d\n", echo_len);
    if (!ft_strncmp(cmd[0], "echo", echo_len))
    {
        printf("Matched 'echo'\n");
        return 1;
    }

    int cd_len = ft_longer(cmd[0], "cd");
    printf("Length of 'cd': %d\n", cd_len);
    if (!ft_strncmp(cmd[0], "cd", cd_len))
    {
        printf("Matched 'cd'\n");
        return 2;
    }

    int pwd_len = ft_longer(cmd[0], "pwd");
    printf("Length of 'pwd': %d\n", pwd_len);
    if (!ft_strncmp(cmd[0], "pwd", pwd_len))
    {
        printf("Matched 'pwd'\n");
        return 3;
    }

    int export_len = ft_longer(cmd[0], "export");
    printf("Length of 'export': %d\n", export_len);
    if (!ft_strncmp(cmd[0], "export", export_len))
    {
        printf("Matched 'export'\n");
        return 4;
    }

    int unset_len = ft_longer(cmd[0], "unset");
    printf("Length of 'unset': %d\n", unset_len);
    if (!ft_strncmp(cmd[0], "unset", unset_len))
    {
        printf("Matched 'unset'\n");
        return 5;
    }

    int env_len = ft_longer(cmd[0], "env");
    printf("Length of 'env': %d\n", env_len);
    if (!ft_strncmp(cmd[0], "env", env_len))
    {
        printf("Matched 'env'\n");
        return 6;
    }

    int exit_len = ft_longer(cmd[0], "exit");
    printf("Length of 'exit': %d\n", exit_len);
    if (!ft_strncmp(cmd[0], "exit", exit_len))
    {
        printf("Matched 'exit'\n");
        return 7;
    }

    printf("No match found\n");
    return 0;
}


void	ft_open(t_toolkit *sh, t_pipe *p, t_fd *fd1, int prev)
{
	while (fd1)
	{
		ft_check_open(p, fd1, prev);
		if (fd1->exp == 1)
			err_exit(sh, fd1->str, "ambiguous redirect", 1);
		if (fd1->token == 6 || fd1->token == 9)
			p->in_fd = fd1->fd;
		else if (!fd1->str || *fd1->str == '\0')
			err_exit(sh, "", "No such file or diectory", 1);
		else if (fd1->token == 4)
			p->in_fd = open(fd1->str, O_RDONLY);
		else if (fd1->token == 5)
			p->out_fd = open(fd1->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
		else if (fd1->token == 7)
			p->out_fd = open(fd1->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (p->in_fd < 0 && (fd1->token == 6 || fd1->token == 9
				|| fd1->token == 4))
			err_exit(sh, fd1->str, NULL, 1);
		if (p->out_fd < 0 && (fd1->token == 5 || fd1->token == 7))
			err_exit(sh, fd1->str, NULL, 1);
		prev = fd1->token;
		fd1 = fd1->next;
	}
}

void	ft_check_open(t_pipe *p, t_fd *cur, int prev)
{
	if (p->in_fd >= 0 && (cur->token == 6 || cur->token == 9 || cur->token == 4)
		&& prev != 6)
	{
		close(p->in_fd);
		p->in_fd = -2;
	}
	if (p->out_fd >= 0 && (cur->token == 5 || cur->token == 7))
	{
		close(p->out_fd);
		p->out_fd = -2;
	}
}

void	check_access(t_toolkit *sh, char **cmd, t_pipe *p)
{
	if (!cmd || !(*cmd))
		err_exit(sh, NULL, NULL, 0);
	else if (!(**cmd))
		err_exit(sh, *cmd, "command not found", 127);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				err_exit(sh, cmd[0], "permission denied", 126);
			p->path = cmd[0];
		}
		else
			err_exit(sh, cmd[0], "No sucha afile or directory", 127);
	}
	else
		check_paths(sh->paths, cmd[0], sh, p);
}

void	check_paths(char **paths, char *cmd, t_toolkit *sh, t_pipe *pipe)
{
	int	i;

	i = 0;
	if (!paths)
		err_exit(sh, cmd, "No such file or directory", 127);
	while (paths[i])
	{
		pipe->path = ft_smart_join(paths[i], "/", cmd);
		if (!pipe->path)
			err_exit(sh, "malloc", NULL, 12);
		if (access(pipe->path, F_OK) == 0)
		{
			if (access(pipe->path, X_OK) != 0)
				err_exit(sh, cmd, "permission denied", 126);
			else
				return ;
		}
		pipe->path = ft_memdel(pipe->path);
		i++;
	}
	err_exit(sh, cmd, "command not found", 127);
}
