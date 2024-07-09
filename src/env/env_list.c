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
			if (tmp->val)
				free (tmp->val);
			tmp->val = ft_strdup(n_value);
			if (!tmp->val)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	env_add_last(t_toolkit *sh, char *name, char *value, int has_value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (1);
	new_env->key = ft_strdup(name);
	new_env->val = ft_strdup(value);
	new_env->next = NULL;
	if (!new_env->key || (has_value && !new_env->val))
	{
		unset_free(new_env);
		return (1);
	}
	add_env_to_list(sh, new_env);
	return (0);
}

/*int	env_add_last(t_toolkit *sh, char *name, char *value, int has_val)
{
	t_env	*new_env;
	t_env	*current;
	
	(void)has_val;
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (1);
	new_env->key = ft_strdup(name);
	new_env->val = value ? ft_strdup(value) : NULL;
	new_env->next = NULL;
	if (!new_env->key || (value && !new_env->val))
	{
		free(new_env->key);
		free(new_env->val);
		free(new_env);
		return (1);
	}
	current = sh->env_lst;
	if (!current)
	{
		sh->env_lst = new_env;
	}
	else
	{
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_env;
	}
	return (0);
}*/

int	add_or_update_env(t_toolkit *sh, char *name, char *value)
{
	t_env	*env;
	int		has_val;

	has_val = 1;
	if (value == NULL)
		has_val = 0;
	env = sh->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, name, ft_strlen(name)) == 0
			&& ft_strlen(env->key) == ft_strlen(name))
		{
			if (env->val)
				free(env->val);
			env->val = ft_strdup(value);
			free(value);
			if (!env->val && value)
				return (err_break(sh, "malloc", NULL, 12));
			return (0);
		}
		env = env->next;
	}
	if (env_add_last(sh, name, value, has_val))
		return (err_break(sh, "malloc", NULL, 12));
	return (0);
}

/*int	add_or_update_env(t_toolkit *sh, char *name, char *value)
{
	t_env	*env;
	int		has_val;

	has_val = 1;
	if (value == NULL)
		has_val = 0;
	env = sh->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, name, ft_strlen(name)) == 0
			&& ft_strlen(env->key) == ft_strlen(name))
		{
			if (env->val)
			{
				free(env->val);
			}
			env->val = ft_strdup(value);
			if (!env->val && value)
				return (err_break(sh, "malloc", NULL, 12));
			return (0);
		}
		env = env->next;
	}
	if (env_add_last(sh, name, value, has_val))
	{
		return (err_break(sh, "malloc", NULL, 12));
	}
	return (0);
}*/
