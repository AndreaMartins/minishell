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
