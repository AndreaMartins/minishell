/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:27:58 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/09 17:28:01 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_toolkit *sh, t_pipe *p)
{
	t_env	*tmp;
	int		output;

	output = p->out_fd;
	if (output < 0)
		output = 1;
	if (sh && sh->env_lst)
	{
		tmp = sh->env_lst;
		while (tmp)
		{
			if (tmp->val != NULL)
			{
				ft_putstr_fd(tmp->key, output);
				ft_putstr_fd("=", output);
				ft_putendl_fd(tmp->val, output);
				ft_putstr_fd("\n", output);
			}
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (1);
}
