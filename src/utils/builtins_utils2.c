/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 14:18:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/15 14:49:50 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	go_prev(t_env_ll **env)
{
	char	*temp;
	char	*back;

	temp = NULL;
	back = find_key_return_value(*env, "OLDPWD");
	if (!back)
		return (write(STDOUT_FILENO, "minishell: cd: OLDPWD not set\n", 30), 1);
	if (chdir(back))
	{
		temp = find_key_return_value(*env, "PWD");
		if (!temp)
			return (1);
		get_key_change_value(env, "PWD", find_key_return_value(*env, "OLDPWD"));
		get_key_change_value(env, "OLDPWD", temp);
		return (0);
	}
	return (1);
}

int	go_back(t_env_ll **env, char *directory)
{
	char	*temp;
	char	*pwd;
	int		i;

	(void)directory;
	temp = NULL;
	i = 0;
	pwd = find_key_return_value(*env, "PWD");
	if (!pwd)
		return (1);
	i = last_slash(pwd);
	temp = ft_strndup(pwd, i);
	if (!temp)
		return (0);
	if (chdir(temp) == 0)
	{
		if (!change_pwd(env, temp))
			return (ft_free(&temp), 1);
		return (0);
	}
	cd_lost_parent_err();
	ft_free(&temp);
	return (1);
}

int	go_home(t_env_ll **env, char *directory)
{
	char	*temp;

	temp = NULL;
	if (chdir(find_key_return_value(*env, "HOME")) == -1)
	{
		if (errno == ENOENT)
			return (print_file_dir_err(find_key_return_value(*env, "HOME"),
					true), 1);
		return (write(STDOUT_FILENO, "cd: HOME not set\n", 17), 1);
	}
	find_key_free_value(env, "OLDPWD");
	temp = find_key_return_value(*env, "PWD");
	get_key_change_value(env, "OLDPWD", temp);
	get_key_change_value(env, "PWD", ft_strdup(find_key_return_value(*env,
				"HOME")));
	if (directory && !ft_strncmp(directory, "~", 1))
		return (-1);
	else
		return (0);
}

void	put_node_at_end(t_env_ll **env, t_env_ll **node)
{
	t_env_ll	*curr;

	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = *node;
	(*node)->prev = curr;
}

int	valid_identifier_check(char c)
{
	if ((c > 122 && c < 127) || (c > 90 && c < 95) || (c < 65 && c > 58)
		|| (c < 65 && c > 58) || (c < 48))
		return (0);
	else
		return (1);
}
