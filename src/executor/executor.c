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


void child_process(t_toolkit *sh, t_pipe *p, int flag)
{
    printf("Entering child_process with flag: %d\n", flag);

    init_signals(N_INTERACT);

    if (!flag)
    {
        printf("Closing sh->exe->fdp[0]: %d\n", sh->exe->fdp[0]);
        close(sh->exe->fdp[0]);
        sh->exe->fdp[0] = -2;
    }

    ft_open(sh, p, p->fd_lst, -1);
    printf("ft_open completed\n");

    if (p->builtin)
    {
        printf("Executing built-in command\n");
        exit(exec_builtin(sh, p));
    }

    check_access(sh, p->cmd, p);
    printf("check_access completed\n");

    ft_redir(sh, p);
    printf("ft_redir completed\n");

    printf("Executing command: %s\n", p->path);
    if (execve(p->path, p->cmd, sh->env) == -1)
    {
        err_exit(sh, "execve", NULL, 14);
    }

    // This point is reached only if execve fails
    printf("Exiting child_process\n");
}

int last_child(t_toolkit *sh, t_pipe *p)
{
    printf("Entering last_child function\n");

    p->builtin = check_builtin(p->cmd);
    printf("p->builtin: %d\n", p->builtin);

    if (!sh->pipes && sh->pipe_lst->builtin)
    {
        printf("Executing built-in command from pipe_lst\n");
        sh->exit = exec_builtin(sh, p);
        return 0;
    }

    sh->exe->pid = fork();
    if (sh->exe->pid < 0)
    {
        printf("Fork failed\n");
        return err_break(sh, "fork", NULL, 12);
    }
    else if (sh->exe->pid == 0)
    {
        printf("Child process executing child_process\n");
        child_process(sh, p, 1);
    }

    if (sh->pipes && p->in_fd >= 0)
    {
        printf("Closing p->in_fd: %d\n", p->in_fd);
        close(p->in_fd);
    }

    printf("Exiting last_child function\n");
    return 0;
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

int exec_builtin(t_toolkit *sh, t_pipe *p)
{
    printf("Entering exec_builtin function\n");
    printf("p->builtin: %d\n", p->builtin);

    if (!sh->pipes && ft_open_built(sh, p, p->fd_lst, -1))
    {
        printf("Executing ft_open_built\n");
        return sh->exit;
    }

    switch (p->builtin)
    {
        case 1:
            printf("Executing ft_echo\n");
            return ft_echo(sh, p);
        case 2:
            printf("Executing ft_cd\n");
            return ft_cd(sh, p);
        case 3:
            printf("Executing ft_pwd\n");
            return ft_pwd(sh, p);
        case 4:
            printf("Executing ft_export\n");
            return ft_export(sh, p);
        case 5:
            printf("Executing ft_unset\n");
            return ft_unset(sh, p);
        case 6:
            if (sh->paths)
            {
                printf("Executing ft_env\n");
                return ft_env(sh, p);
            }
            else
            {
                printf("Paths not set: %s\n", p->cmd[0]);
                err_break(sh, p->cmd[0], "No such file or directory", 127);
                break;
            }
        case 7:
            printf("Executing ft_exit\n");
            return ft_exit(sh);
        default:
            printf("Default case: returning sh->exit\n");
            return sh->exit;
    }

    printf("Exiting exec_builtin function\n");
    return sh->exit;
}
