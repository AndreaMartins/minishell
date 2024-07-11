/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:27:26 by andmart2          #+#    #+#             */
/*   Updated: 2024/04/16 12:50:31 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



/*char	*get_cd_path(int option, t_toolkit *sh)
{
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		if (update_oldpwd(sh) != 0)
			return (NULL);
		env_path = ft_get_value(sh, "HOME");
		if (!env_path)
			ft_putstr_fd("minishell : cd: HOME not set\n", 2);
		if (!env_path)
			return (NULL);
	}
	else if (option == 1)
	{
		env_path = ft_get_value(sh, "OLDPWD");
		if (!env_path)
			ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
		if (!env_path)
			return (NULL);
		if (update_oldpwd(sh) != 0)
			return (NULL);
	}
	return (env_path);
}*/

int	go_to_path(int option, t_toolkit *sh)
{
	char	*env_path;
	int		ret;
	char	*new_pwd;

	env_path = get_cd_path(option, sh);
	if (!env_path)
		return (1);
	ret = chdir(env_path);
	if (ret == 0 && option == 1)
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			printf("%s\n", new_pwd);
			free(new_pwd);
		}
	}
	return (ret);
}

/*int	change_directory(t_toolkit *sh, const char *path)
{
	int		cd_ret;
	char	*new_pwd;

	cd_ret = 0;
	new_pwd = NULL;
	if (path && path[0])
	{
		if (update_oldpwd(sh) != 0)
			return (-1);
		cd_ret = chdir(path);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
		{
			print_error((char *[]){"cd", (char *)path, NULL});
		}
		else
		{
			new_pwd = getcwd(NULL, 0);
			if (new_pwd)
			{
				add_or_update_env(sh, "PWD", new_pwd);
				free(new_pwd);  // Free after updating environment variable
				new_pwd = NULL; // Reset pointer to avoid accidental reuse
			}
		}
	}
	return (cd_ret);
}*/

/*int	ft_cd(t_toolkit *sh, t_pipe *p)
{
	int cd_ret;
	char **args;

	args = p->cmd;
	cd_ret = 0;
	if (!args[1] || args[1][0] == '~')
		return (go_to_path(0, sh));

	if (ft_strcmp(args[1], "-") == 0)
	{
		cd_ret = go_to_path(1, sh);
		char *oldpwd = ft_get_value(sh, "OLDPWD");
		if (oldpwd)
			add_or_update_env(sh, "PWD", oldpwd);
	}
	else
	{
		cd_ret = change_directory(sh, args[1]);
	}

	return (cd_ret);
}*/

/*menos de 25 lineas */

char *get_env_path(int option, t_toolkit *sh, const char *var, const char *msg) {
    char *env_path = ft_get_value(sh, var);
    if (!env_path)
        ft_putstr_fd(msg, 2);
    return env_path;
}

char *get_cd_path(int option, t_toolkit *sh) {
    if (option == 0) {
        if (update_oldpwd(sh) != 0)
            return NULL;
        return get_env_path(0, sh, "HOME", "minishell : cd: HOME not set\n");
    } else if (option == 1) {
        char *env_path = get_env_path(1, sh, "OLDPWD", "minishell : cd: OLDPWD not set\n");
        if (env_path && update_oldpwd(sh) != 0)
            return NULL;
        return env_path;
    }
    return NULL;
}


int handle_chdir_result(t_toolkit *sh, int cd_ret, char *new_pwd) {
    if (cd_ret != 0) {
        print_error((char *[]){"cd", (char *)path, NULL});
    } else {
        new_pwd = getcwd(NULL, 0);
        if (new_pwd) {
            add_or_update_env(sh, "PWD", new_pwd);
            free(new_pwd);
        }
    }
    return cd_ret;
}

int change_directory(t_toolkit *sh, const char *path) {
    int cd_ret = 0;
    if (path && path[0]) {
        if (update_oldpwd(sh) != 0)
            return -1;
        cd_ret = chdir(path);
        if (cd_ret < 0)
            cd_ret *= -1;
        return handle_chdir_result(sh, cd_ret, NULL);
    }
    return cd_ret;
}


int ft_cd(t_toolkit *sh, t_pipe *p) {
    char **args = p->cmd;
    if (!args[1] || args[1][0] == '~')
        return go_to_path(0, sh);

    if (ft_strcmp(args[1], "-") == 0) {
        int cd_ret = go_to_path(1, sh);
        char *oldpwd = ft_get_value(sh, "OLDPWD");
        if (oldpwd)
            add_or_update_env(sh, "PWD", oldpwd);
        return cd_ret;
    }
    return change_directory(sh, args[1]);
}

