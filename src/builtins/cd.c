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
#include <limits.h>
#include <unistd.h>

void	print_error(char **args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (args[2])
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		perror(args[1]);
	}
}

int update_oldpwd(t_toolkit *sh)
{
    char cwd[PATH_MAX];

    // Print a debug message to indicate function entry
    printf("Entering update_oldpwd function...\n");

    // Attempt to get the current working directory
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        // Print debug message and error code if getcwd fails
        printf("getcwd failed, returning -1\n");
        return (-1);
    }

    // Print debug message with the current directory path
    printf("Current directory: %s\n", cwd);

    // Attempt to update the environment variable "OLDPWD"
    if (env_val_update(sh->env_lst, "OLDPWD", cwd))
    {
        // Print debug message if env_val_update returns true
        printf("env_val_update returned true, returning 1\n");
        return (1);
    }

    // Print debug message indicating successful update and return 0
    printf("OLDPWD updated successfully, returning 0\n");

    return (0);
}

int go_to_path(int option, t_toolkit *sh)
{
    int ret;
    char *env_path;

    // Print a debug message to indicate function entry
    printf("Entering go_to_path function with option %d...\n", option);

    env_path = NULL;

    if (option == 0)
    {
        // Option 0: Change to HOME directory
        printf("Option is 0: Changing to HOME directory...\n");

        // Update OLDPWD
        update_oldpwd(sh);

        // Get HOME environment variable
        env_path = ft_get_value(sh, "HOME");

        // Check if HOME environment variable is not set
        if (!env_path)
        {
            printf("HOME environment variable not set\n");
            ft_putstr_fd("minishell : cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (option == 1)
    {
        // Option 1: Change to OLDPWD directory
        printf("Option is 1: Changing to OLDPWD directory...\n");

        // Get OLDPWD environment variable
        env_path = ft_get_value(sh, "OLDPWD");

        // Check if OLDPWD environment variable is not set
        if (!env_path)
        {
            printf("OLDPWD environment variable not set\n");
            ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
            return (1);
        }

        // Update OLDPWD
        update_oldpwd(sh);
    }

    // Print the directory path being changed to
    printf("Changing directory to: %s\n", env_path);

    // Attempt to change directory to env_path
    ret = chdir(env_path);

    // Print debug message with return value of chdir
    printf("chdir returned: %d\n", ret);

    // Return the return value of chdir
    return (ret);
}

int ft_cd(t_toolkit *sh, t_pipe *p)
{
    char **args;
    int cd_ret;

    // Print a debug message to indicate function entry
    printf("Entering ft_cd function...\n");

    cd_ret = 0;
    args = p->cmd;

    // Check if no arguments or argument starts with '~'
    if (!args[1] || args[1][0] == '~')
    {
        printf("No arguments or argument starts with '~', calling go_to_path(0, sh)...\n");
        return (go_to_path(0, sh));
    }

    // Check if argument is '-'
    if (ft_strcmp(args[1], "-") == 0)
    {
        printf("Argument is '-', calling go_to_path(1, sh)...\n");
        cd_ret = go_to_path(1, sh);
        add_or_update_env(sh, "PWD", ft_get_value(sh, "OLDPWD"));
    }
    else
    {
        // Normal path change
        printf("Normal path change, calling update_oldpwd(sh)...\n");
        update_oldpwd(sh);

        // Change directory to specified path
        if (args[1][0])
        {
            printf("Changing directory to: %s\n", args[1]);
            cd_ret = chdir(args[1]);
        }

        // Check for error in cd_ret
        if (cd_ret < 0)
        {
            cd_ret *= -1;
            printf("chdir failed, cd_ret is now: %d\n", cd_ret);
        }

        // Print error if cd_ret is not 0
        if (cd_ret != 0)
        {
            printf("Printing error message...\n");
            print_error(args);
        }

        // Update environment variable "PWD"
        printf("Updating environment variable 'PWD'...\n");
        add_or_update_env(sh, "PWD", getcwd(NULL, 0));
    }

    // Print debug message before returning cd_ret
    printf("Exiting ft_cd function, returning cd_ret: %d\n", cd_ret);

    return (cd_ret);
}
