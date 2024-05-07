/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:04:08 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/05/07 18:04:12 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
If token = 1 - It's a word (token 1) 0
if token = 3 - it's a string "" (token 3) 1
if token = 2 - it's a string '' (token 3) - no expansion
Q is always starting -1 - its a flag to check if we are in the double quotes. 
q < 0 - no open quotes
q > 1 - you are inside open quotes
*/
int	check_exp(char *cont, int token, int q)
{
	int	i;

	i = 0;
	if (!cont || (token != WORD && token != DOUBLEQ))
		return (-1);
	while (cont[i] && cont[i + 1])
	{
		if (token == WORD && cont[i] == '\"')
			q *= -1;
		if (token == WORD && q < 0 && cont[i] == '\'')
		{
			i++;
			while (cont[i] && cont[i] != '\'')
				i++;
			if (!cont[i])
				break ;
		}
		else if (cont[i] == '$' && check_chr(cont[i + 1]) > 2)
			break ;
		i++;
	}
	if (!cont[i] || !cont[i + 1])
		return (-1);
	return (i);
}

