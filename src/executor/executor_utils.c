/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:30:06 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/03 20:07:39 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//recomendacion de poner to lower y usar solo strcmp r CmD (con minusculas y mayusculas mezcladas)
int	check_builtin(char **cmd)
{
	if( !cmd || **cmd)
		return(0);
	if(!ft_strncmp(cmd[0], "echo", ft_longer(cmd[0], "echo")))
		return(1);
	if(!ft_strncmp(cmd[0], "cd", ft_longer(cmd[0], "cd")))
		return(2);
	if(!ft_strncmp(cmd[0], "pwd", ft_longer(cmd[0], "pwd"))
		return(3);
	if(!ft_strncmp(cmd[0], "export", ft_longer(cmd[0], "export"))
		return(4);
	if(!ft_strncmp(cmd[0], "unset", ft_longer(cmd[0], "unset"))
		return(5);
	if(!ft_strncmp(cmd[0], "env", ft_longer(cmd[0], "env"))
		return(6);
	if(!ft_strncmp(cmd[0], "exit", ft_longer(cmd[0], "exit"))
		return(7);
	return(0);
}


// void	ft_open(t_toolkit *sh, t_pipe,)
// void ft_check_open()
void check_access()
{
	if(!cmd || !(*cmd))
		err_exit(sh, NULL, NULL, 0);
	else if (!(**cmd))
		err_exit(sh, *cmd,"command not found", 127);
	if (ft_strchr(cmd[0], '/'))
	{
		if(access(cmd[0], F_OK) == 0)
		{
			if(access(cmd[0], X_OK) != 0 )
				err_exit(sh, cmd[0], "permission denied", 126);
			p->path =cmd[0]
		}
		else
			err_exit(sh,cmd[0], "No sucha afile or directory",127); 		
	}
	else
		check_paths(sh->paths, cmd[0], sh, p);
}


void	check_paths()
{
	int i;

	i = 0;
	if(!paths)
		err_exit(sh, cmd, "No such file or directory", 127);
	while(paths[i])
	{
		//se crea la ruta competa
		pipe->path = ft_smart_join(paths[i],"/",cmd);
		//si no se pudo reservsr la memoria se da error
		if(!pipe->path)
			err_exit(sh, "malloc",NULL, 12);
		//se verifica si el comando existe
		if(access(pipe->path, F_OK) == 0)
		{
		//se verific si tiens permiso de ejecucion
			if (access(pipe->path, X_OK) != 0)
				err_exit(sh, cmd, "permission denied", 126);
			else
				return;	
		}
		//si no existe se libera la memoria
		pipe->path = ft_memdel(pipe->path);
		i++;
	}
	err_exit(sh,cmd, "command not found", 127);	
}



