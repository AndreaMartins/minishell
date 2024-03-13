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
	toolkit->args = readline("Hola Juan Carlos>$ ");
	if (!toolkit->args || !ft_strncmp(toolkit->args, "exit", ft_strlen("exit")))
	{
		printf("adios\n");
		exit(EXIT_SUCCESS);
	}
	add_history(toolkit->args);
	minishell_loop(toolkit);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_toolkit	toolkit;

	(void)envp;

	if(argc != 1 || argv[1])
	{
		printf("This programm doesn't accept arguments.\n");
		exit(0);
	}
	
	minishell_loop(&toolkit);
	return (0);
}
