/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:20:38 by andmart2          #+#    #+#             */
/*   Updated: 2024/05/07 14:20:41 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_get_value(t_toolkit *sh, char *key) {
    t_env *tmp;

    if (!sh || !key) {
        //printf("ft_get_value: invalid input, sh = %p, key = %p\n", (void *)sh, (void *)key);
        return NULL;
    }

    //printf("ft_get_value: searching for key = %s\n", key);

    tmp = sh->env_lst;
    while (tmp) {
        //printf("ft_get_value: checking env key = %s\n", tmp->key);
        if (ft_strncmp(key, tmp->key, ft_longer(key, tmp->key)) == 0) {
            //printf("ft_get_value: match found, value = %s\n", tmp->val);
            return tmp->val;
        } else {
            tmp = tmp->next;
        }
    }

    //printf("ft_get_value: key not found\n");
    return NULL;
}

