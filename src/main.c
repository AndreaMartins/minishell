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
	if(check_quotes(sh->args))
		return(error_quotes(sh));
	//process herdoc syntax
	if(heredoc(sh, sh->args, 0))
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

int	main(int argc, char **argv, char **envp)
{
	t_toolkit	tool;
	
	(void)argc;
	(void)envp;
	(void)argv;

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
