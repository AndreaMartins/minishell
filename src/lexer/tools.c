/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:34 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/26 15:46:37 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Check if there is special symbol (<, >, |) and there are quotes,
for expansion.
1. return (1) - the char is NOT a redirection, it's a simple char
2. return (0) - the char is a redirection or space
3. return (2) - the char is a quote (for expansion)
4. return (3) - the char is a number (for expansion)
4. return (4) - the char is a character (for expansion)
*/
int	check_chr(char c)
{
	if (c == 34 || c == 39)
		return (2);
	if ((c > 47 && c < 58) || c == 63)
		return (3);
	else if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == 95)
		return (4);
	else if ((c > 32 && c < 60) || c == '=' || (c > 62 && c < 124) || \
	(c > 124 && c < 127))
		return (1);
	return (0);
}

int	word_in_quotes(char *input, char *q, int j)
{
	char	q;

	*q = input[++j];
	j++;
	while (input[j] && input[j] != *q)
		j++;
	while (input[j] && input[j + 1] && input[j + 1] != ' '
		&& check_chr(input[j + 1]) != 2)
		j++;
	return (j);
}
