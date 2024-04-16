/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:03:45 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/19 17:03:47 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_add(t_fd **hd_list, t_fd *new)
{
	t_fd	*tmp;

	if (!*hd_list)
	{
		*hd_list = new;
		return ;
	}
	tmp = *hd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}