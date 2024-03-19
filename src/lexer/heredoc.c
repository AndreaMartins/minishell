/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:19:47 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/19 16:19:51 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int heredoc(t_toolkit *tool)
{
	int		i;
	char	*str;

	i = 0;
	str = tool->args;
	if (!ft_strnstr(str, "<<", ft_strlen(str)))
		return (0);
	while (str[i])
	{
		i = wheredoc(str, 0);
		if (i <= 0)
			return (0);
		str = str + i;
		set_new_fd(tool, i);
		i = 0;
	}
}

int	wheredoc(char *str, int i)
{
	while (str[i])
	{
		while (str[i] != '<')
			i++;
		if (str[i] && str[i + 1] == '<')
			return (i);
		i++;
	}
	return (-1);
}
