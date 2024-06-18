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

int g_sig_rec;

/*int minishell_loop(t_toolkit *sh)
{
    // Initialize signal
    init_signals(NORM);
    printf("Debug: Initialized signals.\n");

    do_sigign(SIGQUIT);
    printf("Debug: Ignored SIGQUIT signal.\n");

    sh->args = readline("Hola Juan Carlos$> ");
    printf("Debug: Readline input: %s\n", sh->args);

    // If readline returns null
    if (!sh->args)
        return (ft_exit(sh));

    // After getting input ignore SIGINT signal
    do_sigign(SIGINT);
    printf("Debug: Ignored SIGINT signal.\n");

    // Add input line to shell history
    add_history(sh->args);
    printf("Debug: Added input to history.\n");

    // Check validity of input
    if (check_input(sh->args)) {
        printf("Debug: Input check failed.\n");
        return (0);
    }
    printf("Debug: Input is valid.\n");

    // Check pre-quote issues
    if (check_quotes(sh->args)) {
        printf("Debug: Quote check failed.\n");
        return (error_quotes(sh));
    }
    printf("Debug: Quotes are valid.\n");

    // Process heredoc syntax
    if (heredoc(sh, sh->args, 0)) {
        printf("Debug: Heredoc processing failed.\n");
        return (1);
    }
    printf("Debug: Heredoc processed.\n");

    // Tokenize input using lexer
    if (lexer(sh, sh->args)) {
        printf("Debug: Lexing failed.\n");
        return (1);
    }
    printf("Debug: Lexing successful.\n");

    // Expand environment
    if (expanser(sh, sh->lex_lst, 0)) {
        printf("Debug: Expansion failed.\n");
        return (1);
    }
    printf("Debug: Expansion successful.\n");

    // Check syntax errors
    if (!sh->lex_lst || check_syntax(sh, sh->lex_lst, -1)) {
        printf("Debug: Syntax check failed.\n");
        return (1);
    }
    printf("Debug: Syntax check successful.\n");

    // Parse the token list into commands
    if (!sh->lex_lst || parser(sh, sh->lex_lst, sh->hd_lst, NULL)) {
        printf("Debug: Parsing failed.\n");
        return (1);
    }
    printf("Debug: Parsing successful.\n");

    // Execute the parsed command
    if (executor(sh, sh->pipe_lst, -1, -1)) {
        printf("Debug: Execution failed.\n");
        return (1);
    }
    printf("Debug: Execution successful.\n");

    // If all stages are successful
    return (0);
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
}*/


int minishell_loop(t_toolkit *sh)
{
    init_signals(NORM);
    printf("Debug: Initialized signals.\n");

    do_sigign(SIGQUIT);
    printf("Debug: Ignored SIGQUIT signal.\n");

    sh->args = readline("Hola Juan Carlos$> ");
    printf("Debug: Readline input: %s\n", sh->args);

    if (!sh->args)
        return (ft_exit(sh));

    do_sigign(SIGINT);
    printf("Debug: Ignored SIGINT signal.\n");

    add_history(sh->args);
    printf("Debug: Added input to history.\n");

    if (check_input(sh->args)) {
        printf("Debug: Input check failed.\n");
        return (0);
    }
    printf("Debug: Input is valid.\n");

    if (check_quotes(sh->args)) {
        printf("Debug: Quote check failed.\n");
        return (error_quotes(sh));
    }
    printf("Debug: Quotes are valid.\n");

    if (heredoc(sh, sh->args, 0)) {
        printf("Debug: Heredoc processing failed.\n");
        return (1);
    }
    printf("Debug: Heredoc processed.\n");

    if (lexer(sh, sh->args)) {
        printf("Debug: Lexing failed.\n");
        return (1);
    }
    printf("Debug: Lexing successful.\n");

    if (expanser(sh, sh->lex_lst, 0)) {
        printf("Debug: Expansion failed.\n");
        return (1);
    }
    printf("Debug: Expansion successful.\n");

    if (!sh->lex_lst || check_syntax(sh, sh->lex_lst, -1)) {
        printf("Debug: Syntax check failed.\n");
        return (1);
    }
    printf("Debug: Syntax check successful.\n");

    if (!sh->lex_lst || parser(sh, sh->lex_lst, sh->hd_lst, NULL)) {
        printf("Debug: Parsing failed.\n");
        return (1);
    }
    printf("Debug: Parsing successful.\n");

    if (executor(sh, sh->pipe_lst, -1, -1)) {
        printf("Debug: Execution failed.\n");
        return (1);
    }
    printf("Debug: Execution successful.\n");

    return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_toolkit tool;

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

