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

int	minishell_loop(t_toolkit *sh)
{
	//initialize signal
	init_signals(NORM);

	sh->args = readline("test$>");
	//if readline returns null
	if(!sh->args)
		return(ft_exit(sh));
	//after getting input  ignore sigint signal
	do_siging(SIGINT);
	//add input line to shell history
	add_history(sh->args);
	//check validity of input
	if(check_input(sh->args))
		return(0);
	//check pre quote issues	
	if(pre_quotes(sh->args))
		return(quotes_error(sh));
	//process herdoc syntax
	if(ft_herdoc(sh, sh->args, 0))
		return(1);
	//tokenize input using lexer
	if(lexer(sh, sh->args))
		return(1);
	//expand environment
	if(expanser(sh, sh->lex_lst,0))
		return(1);
	//check syntax errors
	if(!sh->lex_lst || check_syntax(sh, sh->lex_lst, -1))
		return(1);
	//parse the token list into commands
	if(!sh->lex_lst || parser(sh, sh->lex_lst, sh->hd_lst, NULL))
		return(1);
	//execute the parsed command
	if(executor(sh, sh->pipe_lst, -1, -1))
		return(1);
	//if all stages are successfull
	return(0);
}

/*int	minishell_loop(t_toolkit *tool)
{
	tool->args = readline("Hola Juan Carlos>$ ");
	if (!tool->args || !ft_strncmp(tool->args, "exit", ft_strlen("exit")))
	{
		printf("adios\n");
		exit(EXIT_SUCCESS);
	}
	add_history(tool->args);
	if (check_quotes(tool->args))
		return (error_quotes(tool));
	//if (heredoc(tool, tool->args, 0))
	//	return (1);
	if (lexer(tool, tool->args))
		return (1);
		
	return (0);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_toolkit	tool;
	
	(void)argc;
	(void)envp;

	g_sig_rec = 0;
	sh_init(&tool, envp);
	while (tool.power_on)
	{
		if(!sh_loop_init(&tool))
			minishell_loop(&tool);
		sh_clean(&tool);
		if(g_sig_rec == 1)
		{
			tool.exit = 1;
			g_sig_rec = 0;
		}
	}
	free_env(&tool);
	return (tool.exit);
}
