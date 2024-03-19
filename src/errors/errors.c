/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:05:52 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/19 13:05:53 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_quotes(t_toolkit *kit)
{
	ft_putstr_fd("minishell: syntax error: Quotes not closed\n", 2);
	kit->exit = 258;
	return (1);
}