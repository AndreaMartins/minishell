/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:56:38 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/16 16:11:50 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void norm_handler(int sig, siginfo_t *data, void *non_used_data)
{
    //printf("norm_handler: Signal received: %d\n", sig);
    (void)data;
    (void)non_used_data;
    if (sig == SIGINT)
    {
        //printf("norm_handler: Handling SIGINT\n");
        //printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
        g_sig_rec = 1;
    }
    return;
}

void child_sigint_handler(int sig)
{
    printf("child_sigint_handler: Signal received: %d\n", sig);
    printf("\nCaught SIGINT in child process, terminating\n");
    exit(130);
}

void do_sigign(int signum)
{
    //printf("do_sigign: Ignoring signal: %d\n", signum);
    struct sigaction signal;

    signal.sa_handler = SIG_IGN;
    signal.sa_flags = SA_RESTART;
    sigemptyset(&signal.sa_mask);
    if (sigaction(signum, &signal, NULL) < 0)
    {
        perror("do_sigign: sigaction failed");
        exit(1);
    }
}

int init_signals(int mode)
{
    //printf("init_signals: Setting up signal handlers for mode: %d\n", mode);
    struct sigaction signal;

    signal.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&signal.sa_mask);
    if (mode == NORM)
    {
        //printf("init_signals: Setting norm_handler\n");
        signal.sa_sigaction = norm_handler;
    }
    else if (mode == CHILD)
    {
        //printf("init_signals: Setting child_sigint_handler\n");
        signal.sa_handler = child_sigint_handler;
    }

    if (sigaction(SIGINT, &signal, NULL) < 0)
    {
        perror("init_signals: sigaction failed for SIGINT");
        exit(1);
    }
    if (sigaction(SIGQUIT, &signal, NULL) < 0)
    {
        perror("init_signals: sigaction failed for SIGQUIT");
        exit(1);
    }

    return 0;
}

void exit_status(t_toolkit *sh, int j)
{
    //printf("exit_status: Checking exit status for processes\n");
    while (++j <= sh->pipes)
    {
        //printf("exit_status: Waiting for process %d\n", j);
        if (sh->exe->pid == wait(&sh->exe->stat))
        {
            if (WIFEXITED(sh->exe->stat))
            {
                //printf("exit_status: Process exited normally with status %d\n", WEXITSTATUS(sh->exe->stat));
                sh->exit = WEXITSTATUS(sh->exe->stat);
            }
            else if (WIFSIGNALED(sh->exe->stat))
            {
                if (WTERMSIG(sh->exe->stat) == SIGINT)
                {
                    //printf("exit_status: Process terminated by SIGINT\n");
                    //printf("\n");
                    sh->exit = 130;
                }
                else if (WTERMSIG(sh->exe->stat) == SIGQUIT)
                {
                    //printf("exit_status: Process terminated by SIGQUIT\n");
                    sh->exit = 131;
                    //printf("Quit: 3\n");
                }
            }
        }
    }
}
