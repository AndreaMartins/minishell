/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:17:38 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/13 13:17:42 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Trims all spaces and sets a space token*/
t_lexer	*rd_space(char *input, int *i)
{
	char		*new_str;
	int			j;

	new_str = NULL;
	j = 0;
	while (input[j + 1] && input[j + 1] == ' ')
		j++;
	new_str = malloc(sizeof(char) * 2);
	if (!new_str)
		return (NULL);
	new_str[0] = ' ';
	new_str[1] = '\0';
	*i += j;
	return (lex_new(new_str, SPACE)); // TO - DO function
}

t_lexer	*read_word(char	*input, int i)
{

}

t_lexer	*rd_redirection(t_toolkit *tool, char *input, int *i)
{
	int			j;


}

int lexer(t_toolkit *tool, char	*input)
{
	t_lexer	*new;
	int		i;

	new = NULL;
	i = -1;

	while (input[++i])
	{
		if (input[i] == ' ')
			new = rd_space(&input[i], &i);
		else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			new = rd_redirection(&tool, input, &i);
		else if (input[i] == 39 || input[i] == 34)
			new = rd_in_quotes(&tool, &i);
		else
			new = rd_word(&tool, &i);
		if (!new)
			return (EXIT_FAILURE); // TO - DO error function
		else
			lex_add(&tool, new); // TO - DO function
	}

}