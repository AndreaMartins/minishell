/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:52:42 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/05/07 17:52:43 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_hd(t_toolkit *tool, char *cont, int token)
{
	if (token == HEREDOC_NO_EXP)
		return (cont);
	if (check_exp(cont, 3, -1) < 0)
		return (cont);
	if (exp_init(tool))
		return (ft_memdel(cont));
	cont = expand_str(tool, cont, 3, -1);
	return (cont);
}