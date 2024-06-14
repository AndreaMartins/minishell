/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:01 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/16 15:33:32 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_redir(t_toolkit *sh, t_pipe *p)
{
	fprintf(stderr, "Entering ft_redir\n");
	fprintf(stderr, "p->in_fd: %d, p->out_fd: %d\n", p->in_fd, p->out_fd);

	if (p->in_fd >= 0)
	{
		fprintf(stderr, "Redirecting input: dup2(%d, STDIN_FILENO)\n", p->in_fd);
		if (dup2(p->in_fd, STDIN_FILENO) < 0)
		{
			err_exit(sh, "dup2", NULL, 1);
		}
		close(p->in_fd);
		p->in_fd = -2;
	}

	if (p->out_fd >= 0)
	{
		fprintf(stderr, "Redirecting output: dup2(%d, STDOUT_FILENO)\n", p->out_fd);
		if (dup2(p->out_fd, STDOUT_FILENO) < 0)
		{
			err_exit(sh, "dup2", NULL, 1);
		}
		close(p->out_fd);
		p->out_fd = -3;
	}
	
	fprintf(stderr, "p->in_fd: %d, p->out_fd: %d\n", p->in_fd, p->out_fd);
	fprintf(stderr, "Exiting ft_redir\n");
}


void	child_process(t_toolkit *sh, t_pipe *p, int option)
{
	printf("Entering child_process with option: %d\n", option);
	init_signals(N_INTERACT);

	if (!option)
	{
		printf("Closing sh->exe->fdp[0]: %d\n", sh->exe->fdp[0]);
		close(sh->exe->fdp[0]);
		sh->exe->fdp[0] = -2;
	}

	ft_open(sh, p, p->fd_lst, -1);

	if (p->builtin)
	{
		printf("Executing builtin command\n");
		exit(exec_builtin(sh, p));
	}

	check_access(sh, p->cmd, p);
	ft_redir(sh, p);

	printf("Executing command: %s\n", p->path);
	if (execve(p->path, p->cmd, sh->env) == -1)
		err_exit(sh, "execve", NULL, 14);

	printf("Exiting child_process\n");
}

int	last_child(t_toolkit *sh, t_pipe *p)
{
	printf("Entering last_child\n");

	p->builtin = check_builtin(p->cmd);
	printf("p->builtin: %d\n", p->builtin);

	if (!sh->pipes && sh->pipe_lst->builtin)
	{
		printf("Executing builtin command in last_child\n");
		sh->exit = exec_builtin(sh, p);
		return (0);
	}

	printf("Forking last child process\n");
	sh->exe->pid = fork();

	if (sh->exe->pid < 0)
	{
		printf("Fork failed\n");
		return (err_break(sh, "fork", NULL, 12));
	}
	else if (sh->exe->pid == 0)
	{
		printf("Running child_process from last_child\n");
		child_process(sh, p, 1);
	}

	if (sh->pipes && p->in_fd >= 0)
	{
		printf("Closing p->in_fd: %d\n", p->in_fd);
		close(p->in_fd);
	}

	printf("Exiting last_child\n");
	return (0);
}

int executor(t_toolkit *sh, t_pipe *p, int i, int j)
{
    printf("Entering executor function\n");

    while (++i < sh->pipes)
    {
        printf("Loop iteration: %d\n", i);
        
        p->builtin = check_builtin(p->cmd);
        printf("p->builtin: %d\n", p->builtin);
        
        if (pipe(sh->exe->fdp) < 0)
        {
            printf("Pipe creation failed\n");
            return (err_break(sh, "pipe", "Broken pipe", 32));
        }
        
        p->out_fd = sh->exe->fdp[1];
        printf("Created pipe: sh->exe->fdp[1]: %d\n", sh->exe->fdp[1]);

        sh->exe->pid = fork();
        if (sh->exe->pid < 0)
        {
            printf("Fork failed\n");
            return (err_break(sh, "fork", NULL, 12));
        }
        else if (sh->exe->pid == 0)
        {
            printf("Child process executing\n");
            child_process(sh, p, 0);
        }
        
        close(sh->exe->fdp[1]);
        printf("Closed sh->exe->fdp[1]: %d\n", sh->exe->fdp[1]);

        if (p->in_fd >= 0)
        {
            close(p->in_fd);
            printf("Closed p->in_fd: %d\n", p->in_fd);
        }

        p = p->next;
        p->in_fd = sh->exe->fdp[0];
        printf("Updated p->in_fd to sh->exe->fdp[0]: %d\n", sh->exe->fdp[0]);
    }

    printf("Executing last_child function\n");
    last_child(sh, p);
    
    printf("Exiting executor function\n");
    exit_status(sh, j);

    return 0;
}

int	exec_builtin(t_toolkit *sh, t_pipe *p)
{
	printf("Entering exec_builtin with p->builtin: %d\n", p->builtin);

	if (!sh->pipes && ft_open_built(sh, p, p->fd_lst, -1))
		return (sh->exit);

	switch (p->builtin)
	{
		case 1:
			return (ft_echo(sh, p));
		case 2:
			return (ft_cd(sh, p));
		case 3:
			return (ft_pwd(sh, p));
		case 4:
			return (ft_export(sh, p));
		case 5:
			return (ft_unset(sh, p));
		case 6:
			if (sh->paths)
				return (ft_env(sh, p));
			else
				return (err_break(sh, p->cmd[0], "No such file or directory", 127));
		case 7:
			return (ft_exit(sh));
		default:
			return (sh->exit);
	}

	printf("Exiting exec_builtin\n");
}
