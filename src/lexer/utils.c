/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:26:16 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/05/29 14:26:17 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	This function receives 2 strings and returns the length
	of the longer one 
*/
int	ft_longer(char *str, char *key)
{
	int	len;

	if (ft_strlen(str) > ft_strlen(key))
		len = ft_strlen(str);
	else
	{
		len = ft_strlen(key);
	}
	return (len);
}

/*
	Concatenates three input strings (s1, s2, and s3)
	into a single new string. It ensures that all input
	strings are valid and dynamically allocates memory for
	the concatenated result.
*/
char	*ft_triplejoin(char *s1, char *s2, char *s3)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!(s1 && s2 && s3))
		return (0);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
		new[i++] = s2[j++];
	j = 0;
	while (s3[j])
		new[i++] = s3[j++];
	new[i] = '\0';
	return (new);
}

/*
	This function cleans the lex list.
*/
int	lex_clean(t_lexer **lst)
{
	t_lexer	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->str)
		{
			free((*lst)->str);
			(*lst)->str = NULL;
		}
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

/* 
	This function receives an double array and a flag that means:
	1. flag=0 - all the strings in the array are allocated, so it frees them
	2. flag=1 - the strings in the array are NOT allocated, 
			it only iquals them to null
*/
char	**arr_clean(char **cmd, int flag)
{
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd && cmd[i])
	{
		if (!flag)
			cmd[i] = ft_memdel(cmd[i]);
		else
			cmd[i] = NULL;
		i++;
	}
	cmd = ft_memdel(cmd);
	return (NULL);
}
