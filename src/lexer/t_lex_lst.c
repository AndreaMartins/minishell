/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lex_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:18:42 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/04/02 15:18:44 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* function to create lexer nodes */

t_lexer	*lex_new(char *info, t_tokens type)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (ft_memdel(info));
	new_node->str = info;
	new_node->token = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/* function to find the last node of the lexer list*/

t_lexer	*lex_last(t_lexer *lex_list)
{
	while (lex_list && lex_list->next)
		lex_list = lex_list->next;
	return (lex_list);
}

/* function to add lexer nodes to the list */

void	lex_add(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!*lst)
		*lst = new;
		new->prev = NULL;
		return ;
	last = lex_last(*lst);
	last->next = new;
	new->prev = last;
}

/* function to clean the list */

int	lst_clear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (*lst == NULL)
		return (0);
	if ((*lst)->str)
		free((*lst)->str);
	tmp = (*lst)->next;
	free(*lst);
	*lst = NULL;
	return (lst_clear(&tmp));
}
