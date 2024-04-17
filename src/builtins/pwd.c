/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:29:12 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/09 17:29:14 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int ft_pwd(t_toolkit *sh, t_pipe *p)
{
    char *pwd;
    int output;

    output = p->out_fd;
    if(output < 0)
        output = 1;
    pwd = NULL;
    pwd = getcwd (pwd, 0);
    if (!pwd)
    {
        ft_putstr_fd(ft_get_value(sh, "PWD"), output);
    }
    ft_putstr_fd(pwd, output);
    ft_putstr_fd("\n", output);
    free(pwd);
    return(0);
}