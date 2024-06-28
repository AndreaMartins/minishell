/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:11 by andmart2          #+#    #+#             */
/*   Updated: 2024/05/07 14:19:16 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_getkey_node(char *new_key, t_env *list)
{
	t_env	*head;

	head = list;
	while (list->next)
	{
		if (ft_strcmp(new_key, list->key) == 0)
			return (list);
		list = list->next;
	}
	list = head;
	return (NULL);
}

int	env_val_update(t_env *head, char *key, char *n_value)
{
	t_env	*tmp;
	size_t	len;

	tmp = head;
	len = ft_strlen(key);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && len == ft_strlen(tmp->key))
		{
			tmp->val = ft_strdup(n_value);
			if (!tmp->val)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int env_add_last(t_toolkit *sh, char *name, char *value, int has_val) {
    (void)has_val;  // Marcar has_val como no utilizado

    t_env *new_env = (t_env *)malloc(sizeof(t_env));
    if (!new_env) {
        //printf("env_add_last: malloc failed\n");
        return 1;
    }

    new_env->key = ft_strdup(name);
    new_env->val = value ? ft_strdup(value) : NULL;
    new_env->next = NULL;

    if (!new_env->key || (value && !new_env->val)) {
        //printf("env_add_last: strdup failed\n");
        free(new_env->key);
        free(new_env->val);
        free(new_env);
        return 1;
    }

    t_env *current = sh->env_lst;
    if (!current) {
        sh->env_lst = new_env;
    } else {
        while (current->next) {
            current = current->next;
        }
        current->next = new_env;
    }

    //printf("env_add_last: new environment variable added, key = %s, value = %s\n", name, value);
    return 0;
}

int add_or_update_env(t_toolkit *sh, char *name, char *value) {
    t_env *env;
    int has_val;

    has_val = 1;
    if (value == NULL)
        has_val = 0;

    //printf("add_or_update_env: name = %s, value = %s, has_val = %d\n", name, value, has_val);

    env = sh->env_lst;
    while (env != NULL) {
        //printf("add_or_update_env: checking env key = %s\n", env->key);

        if (ft_strncmp(env->key, name, ft_strlen(name)) == 0 && ft_strlen(env->key) == ft_strlen(name)) {
            //printf("add_or_update_env: match found, updating key = %s\n", env->key);

            if (env->val) {
                //printf("add_or_update_env: freeing old value = %s\n", env->val);
                free(env->val);
                //printf("add_or_update_env: value freed successfully\n");
            }

            env->val = ft_strdup(value);
            if (!env->val && value) {
                //printf("add_or_update_env: memory allocation failed for value\n");
                return (err_break(sh, "malloc", NULL, 12));
            }

            //printf("add_or_update_env: value updated successfully\n");
            return (0);
        }

        env = env->next;
    }

    //printf("add_or_update_env: no match found, adding new environment variable\n");
    if (env_add_last(sh, name, value, has_val)) {
        //printf("add_or_update_env: memory allocation failed during env_add_last\n");
        return (err_break(sh, "malloc", NULL, 12));
    }

    //printf("add_or_update_env: new environment variable added successfully\n");
    return (0);
}
