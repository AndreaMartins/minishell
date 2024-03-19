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

int	set_new_fd(t_toolkit *tool, char *str, int i)
{
	t_fd	*new;

	new = malloc(sizeof(t_fd));
	if (!new)
		return (EXIT_FAILURE); // TO - DO error function
	new->next = NULL;
	new->type = 6;
	fd_add(&(tool->hd_lst), new);
	new->str = keyword_hd(new, str, &i, ' ');
	if (!new->str)
		return (EXIT_FAILURE); 	// TO - DO error function
	new->fd = save_hd(tool, new->str, NULL, new->type);
	if (new->fd < 0)
		return (EXIT_FAILURE); // TO - DO error function
	return (0);
}