/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:01 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/03 20:18:16 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*crear err_exit function*/
/*ft_open function*/
/*check_access*/

void	ft_redir(t_toolkit *sh, t_pipe *p)
{
	if (p->in_fd >= 0)
	{
		if (dup2(p->in_fd, STDIN_FILENO) < 0)
			err_exit(sh, "dup2", NULL, 1);
		close(p->in_fd);
		p->in_fd = -2;
	}
	if (p->out_fd >= 0)
	{
		if(dup2(p->out_fd,STDOUT_FILENO) < 0)
			err_exit
	}
}

void	child_process(t_toolkit *sh, t_pipe *p, int option)
{
	init_signals(N_INTERACT);
	if (!option)
	{
		close(sh->exe->fdp[0]);
		sh->exe->fdp[0] = -2;
	}
	ft_open(sh, p, p->fd_lst, -1 );
	if(p->builtin)
		exit(exec_builting (sh,p));
	check_access(sh, p->cmd, p);
	ft_redir(sh, p);
	if(execve(p->path, p->cmd, sh->env) == -1)
		err_exit(sh, "execve", NULL, 14);
}

int	executor(t_toolkit *sh, t_pipe *p, int i, int j)
{
	while (i++ < sh->pipes)
	{
		p->builtin = check_buildin(p->cmd);
		if(pipe(sh->exe->fdp) < 0)

	}
	last_child(sh, p);
	exit_status(sh, j);
	return (0);
}

int	exec_builtin(t_toolkit *sh, t_pipe *p)
{
	if(!sh->pipes && ft_open_built(sh, p, p->fd_lst, -1))
		return(sh->exit);
	if(p->builtin == 1)
		return(ft_echo(sh, p))
	if(p->builtin == 2)
		return(ft_cdho(sh, p))
	if(p->builtin == 3)
		return(ft_pwd(sh, p))
	if(p->builtin == 4)
		return(ft_export(sh, p))	
	if(p->builtin == 5)
		return(ft_unset(sh, p))
	if(p->builtin == 6 && sh->paths)
		return(ft_env(sh, p));
	else if ( p->builtin == 6 && !sh->paths)
		err_break(sh, p->cmd[0], "No such file or directory", 127);
	if(p->builtin == 7)
		return(ft_exit(sh));
	return(sh->exit);
}
