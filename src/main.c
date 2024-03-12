/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:44:23 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/03/12 16:44:33 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell_loop(t_toolkit *toolkit)
{
	toolkit->args = readline("minishell >$ ");
	if (!toolkit->args)
	{
		exit(EXIT_SUCCESS);
	}
	add_history(toolkit->args);
	minishell_loop(toolkit);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;

	t_toolkit	toolkit;

	if(argc != 1)
		printf("This programm doesn't accept arguments.\n");
	minishell_loop(&toolkit);
	return (0);
}
