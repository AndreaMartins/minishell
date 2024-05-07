/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:28:59 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/09 17:29:01 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_export(t_env *eprint, t_pipe *p)
{
    t_env   *tmp;
    int output;

    output = p->out_fd;
    if (output < 1)
        output = 1;
    if (!eprint)
        return(1);
    print_sort_print(eprint);
    tmp = eprint;
    while (tmp)
    {
        ft_putstr_fd("declare -x", output);
        ft_putstr_fd(tmp->env_key, output);
        if(tmp->env_val)
            print_env_fd(tmp, output);
        else
            ft_putstr_fd("\n", output);
        tmp = tmp->next;
    }
    tmp = eprint;
    return(0);
}