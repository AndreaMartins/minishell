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
// void check_access()


void	check_paths()
{

}


 
