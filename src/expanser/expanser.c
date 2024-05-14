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

/*
	Handles the expansion of variables within heredoc content based on the
	specified type.
	It differentiates between types that require expansion and those that don't.
*/
char	*expand_hd(t_toolkit *tool, char *str, int token)
{
	if (token == HEREDOC_NO_EXP)
		return (str);
	if (check_exp(str, 3, -1) < 0)
		return (str);
	if (exp_init(tool))
		return (ft_memdel(str));
	str = expand_str(tool, str, 3, -1);
	return (str);
}

/*
	Expands variables within the given string based on the type, handling
	double quotes and other special characters.
*/
char	*expand_str(t_toolkit *tool, char *str, int token, int i)
{
	if (exp_start(tool, str, token))
		return (NULL);
	while (str[++i])
	{
		if (open_q(tool->exp, str[i], token) || str[i] != '$' || !str[i + 1])
			tool->exp->new[++tool->exp->j] = str[i];
		else
		{
			tool->exp->var = get_var(&str[i + 1]);
			if (!tool->exp->var)
				return (NULL);
			tool->exp->val = check_value(tool, tool->exp->var);
			if (*tool->exp->var == '?' && !tool->exp->val)
				return (NULL);
			while (tool->exp->val && tool->exp->val[++tool->exp->k])
				tool->exp->new[++tool->exp->j] = tool->exp->val[tool->exp->k];
			i += ft_strlen(tool->exp->var);
			exp_spc_clean(tool->exp);
		}
	}
	tool->exp->new[++tool->exp->j] = '\0';
	if (token == DOUBLEQ)
		tool->exp->str = ft_memdel(tool->exp->str);
	return (tool->exp->new);
}

/*
	Function designed to expand the $ into the command.
*/
int	expanser(t_toolkit *t, t_lexer *head, int flag)
{
	if (exp_init(t))
		return (1);
	while (t->lex_lst)
	{
		if (t->lex_lst->token == 3 && check_exp(t->lex_lst->str, 3, -1) >= 0)
		{
			t->lex_lst->str = expand_str(t, t->lex_lst->str, 3, -1);
			if (!t->lex_lst->str)
				return (err_break(tool_re(&t, head, NULL),
						"malloc", NULL, 12));
		}
		else if (!flag)
		{
			if (exp_quotes(t, &head, &flag))
				return (err_break(tool_re(&t, head, NULL), "malloc", NULL, 12));
		}
		if (t->lex_lst && t->lex_lst->token > 0
			&& t->lex_lst->token < 4 && flag)
			flag = 0;
		if (t->lex_lst)
			t->lex_lst = t->lex_lst->next;
	}
	shell_re(&t, head, NULL);
	return (0);
}
