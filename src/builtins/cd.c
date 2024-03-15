/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 12:09:22 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/15 11:01:32 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_in_dir(t_env_ll **env, char *directory)
{
	t_env_ll	*node;
	char		*path;

	if (directory[0] != '/')
		directory = ft_strjoin("/", directory);
	if (!directory)
		return (1);
	node = find_key(*env, "PWD");
	path = ft_strjoin(node->value, directory);
	if (!path)
		return (ft_free(&directory), 0);
	if (chdir(path) == -1)
	{
		print_file_dir_err(directory, true);
		ft_free(&directory);
		ft_free(&path);
		return (1);
	}
	ft_free(&directory);
	ft_free(&path);
	change_pwd(env, get_curr_dir());
	return (0);
}

int	relative_path(t_env_ll **env, char *directory)
{
	int	status;

	if (!directory || !ft_strncmp(directory, "~", 1))
	{
		status = go_home(env, directory);
		if (status == 0 || status == 1)
			return (status);
		else
			directory = ft_strdup(directory + 1);
	}
	if (!ft_strncmp(directory, ".", 2) || !ft_strncmp(directory, "./",
			ft_strlen(directory)))
		return (0);
	if (!ft_strncmp(directory, "-", 1))
		return (go_prev(env));
	if (!ft_strncmp(directory, "..", 3))
		return (go_back(env, directory));
	return (find_in_dir(env, directory));
}

int	absolute_path(t_env_ll **env, char *directory)
{
	if (chdir(directory) == 0)
		change_pwd(env, get_curr_dir());
	else
		return (print_file_dir_err(directory, true), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cd(t_env_ll **env, char **directory)
{
	int	count;

	count = 0;
	while (directory[count])
		count++;
	if (count > 1)
		return (write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34),
			1);
	if (!directory[0] || directory[0][0] != '/')
		return (relative_path(env, directory[0]));
	else
		return (absolute_path(env, directory[0]));
}
