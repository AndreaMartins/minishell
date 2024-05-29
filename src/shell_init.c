/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:15:11 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/05/24 20:15:13 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	The shell_re function restores the initial positions of the lexer and 
	heredoc lists within the t_toolkit structure to their original states after 
	they have been iterated over. 
*/
t_toolkit	*shell_re(t_toolkit **tool, t_lexer *lex, t_fd *hd)
{
	if (lex)
		(*tool)->lex_lst = lex;
	if (hd)
		(*tool)->hd_lst = hd;
	return (*tool);
}

int		sh_lopp_init(t_toolkit *sh)
{
	sh->pipes = 0;
	sh->check = 0;

	if(ft_get_value(sh, "PATH"))
	{
		sh->paths = ft_split(ft_get_value(sh, "PATH"), ':');
		if(!sh->paths)
			return(err_break(sh, "malloc", NULL, 12));
	}
	if(allocate_exe(sh))
		return(err_break(sh, "malloc", NULL, 12));
	return(0);
}

int	allocate_exe(t_toolkit *sh)
{
	t_exec *new;

	new = malloc(sizeof(t_exec));
	if(!new)
		return(1);
	
	new->fdp[0]= -2;
	new->fdp[1] = -2;
	sh->exe = new;
	return(0);
}