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
//verifica si el descriptor del archivo de entrada es mayor o igual a 0
	if (p->in_fd >= 0)
	{
//duplica el descriptor de archivo y si hay error se va
		if (dup2(p->in_fd, STDIN_FILENO) < 0)
			err_exit(sh, "dup2", NULL, 1);
		close(p->in_fd);
		//cierra y se estable en -2 para indircar que no esta uso
		p->in_fd = -2;
	}
//verifica si descriptor de salida es mayor igual a 0
	if (p->out_fd >= 0)
	{
	//duplica y si hay error se va
		if(dup2(p->out_fd,STDOUT_FILENO) < 0)
			err_exit(sh, "dup2", NULL, 1);
		close(p->out_fd)
		p->out_fd = -2;
	}
}

void	child_process(t_toolkit *sh, t_pipe *p, int option)
{
//iniciar senhales
	init_signals(N_INTERACT);
	//si option es igual 0 se cierra el descriptor y se establece -2
	if (!option)
	{
		close(sh->exe->fdp[0]);
		sh->exe->fdp[0] = -2;
	}
	//manejar redireccion de archivos
	ft_open(sh, p, p->fd_lst, -1 );
	//si es verdadero se ejecuta exec builtin y se sale del proceso
	if(p->builtin)
		exit(exec_builting (sh,p));
	//verificar si el usuario tiene el permisod e eejecutar el comando
	check_access(sh, p->cmd, p);
	//manejar la redireccion del preoceso hijo
	ft_redir(sh, p);
	//ejecutar el comando especificado y hay error se va
	if(execve(p->path, p->cmd, sh->env) == -1)
		err_exit(sh, "execve", NULL, 14);
}

int	last_child(t_toolkit *sh, t_pipe *p)
{
	//verificar si p->cmd es un comando integrado
	p->builtin = check_builtin(p->cmd);
	//verifica si no hay tuberias y si el ultimo elemento de la linea de tuberias es un cmd integrado
	if(!sh->pipes && sh->pipe_lst->builtin)
	{
		sh->exit = exec_builtin(sh, p);
		return(0);
	}
	//nuevo proceso hijo usando fork y le pid hijo se guarda
	sh->exe->pid = fork();
	//si el fork es negativo
	if (sh->exe->pid < 0)
		return(err_break(sh, "fork", NULL, 12));
	//si el fork es igual a 0
	else if(sh->exe->pid == 0)
		child_proces(sh, p,1);
	//si hay tuberias y el descriptor es mayor o igual a 0 
	if (sh->pipes && p->in_fd >= 0)
		close(p->in_fd);
	return(0);
}

int	executor(t_toolkit *sh, t_pipe *p, int i, int j)
{
//bucle se ejecuta mientrs i sea menor al numero de tuberias
	while (i++ < sh->pipes)
	{
		//verifica si el comando es un comando interno
		p->builtin = check_buildin(p->cmd);
		//crea una tuberia
		if (pipe(sh->exe->fdp) < 0)
			return (err_break(sh, "pipe", "Broken pipe", 32);
		//guarda el descriptor de archivo de escritura d ela tuberia
		p-> out_fd = sh -> exe -> fdp[1];
		//crea un nuevo proceso hijo usando fork
		sh->exe->pid = fork();
		//si fork es neegativo sale un error
		if (sh->exe->pid < 0)
			return(err_break(sh, "fork", NULL, 12));
		//si el pid es 0 se llama a child_process
		else if (sh->exe->pid = 0)
			child_process(sh, p, o);//FUNCION QUE ESTA POR OTRO LADO
		//se cierra el descriptor de archivo de escritura de la tuberia en el proceso padre
		close(sh->exe->fdb[1]);
		//se cierra el descriptor de archivo de lectura dee la tuberia si es mayor o igual a o
		if (p->in_fd >= 0)
			close (p ->in_fd)
			//avanza al sigueinte nodo
		p = p->next;
		p->in_fd = sh->exe->fdp[0];
	}
	last_child(sh, p);
	exit_status(sh, j);
	return (0);
}

int	exec_builtin(t_toolkit *sh, t_pipe *p)
{
	//verifica si no hay tuberias
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
	//si builtin es igual a 6 y no hay paths
	if(p->builtin == 6 && sh->paths)
		return(ft_env(sh, p));
	else if ( p->builtin == 6 && !sh->paths)
		err_break(sh, p->cmd[0], "No such file or directory", 127);
	if(p->builtin == 7)
		return(ft_exit(sh));
	return(sh->exit);
}
