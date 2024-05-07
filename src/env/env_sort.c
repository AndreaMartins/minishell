/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:11 by andmart2          #+#    #+#             */
/*   Updated: 2024/05/07 14:16:34 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_sort_print(t_env *env)
{
    t_env   *tmp;
    char    *tmp_name;
    char    *tmp_value;

    tmp = env;
    while(tmp != NULL)
    {
        if(tmp->next != NULL)
        {
            if(ft_strcmp(tmp->env_key, tmp->next->env_key) > 0)
            {
                tmp_name = tmp->env_key;
                tmp_value = tmp->env_val;
                tmp->env_key = tmp->next->env_key;
                tmp->env_val = tmp->next->env_val;
                tmp->next->env_key = tmp_name;
                tmp->next->env_val = tmp_value;
                tmp = env;
            }
        }
        tmp = tmp->next;
    }
}