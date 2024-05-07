/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:28:37 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/09 17:28:40 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_export(t_toolkit *sh, t_pipe *p)
{
    t_env   *tmp_env;
    char    **t_cmd;
    int     err;
    int     i;

    //Initialize error flag and get command tokens
    err = 0;
    tmp_env = sh->env_lst;
    t_cmd = p->cmd;
    i = 1;

    //if not arg provided, print the current env
    if(!t_cmd)
        return(print_export(tmp_env, p));
    
    //Iterate through command arguments
    while (t_cmd[i])
    {
        if (!err)
            err = handle_args(sh, t_cmd[i]);
        else
            handle_args(sh, t_cmd[i]);
        i++;
    }
    // Clean up the environment variable and update the environment array
    if(sh->env)
        sh->env = arr_clean(sh->env, 0);
        sh->env = env_converter(sh->env_lst);

    //Return the final error status
    return(err).
}