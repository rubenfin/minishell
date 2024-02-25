/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 12:09:22 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/25 11:14:27 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	last_slash(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
			x = i;
		i++;
	}
	if (x == 0)
		x = 1;
	return (x);
}

void	relative_path(t_env_ll **env, char *directory)
{
	t_env_ll	*node;
	char		*path;
	char		*temp;
	int			i;

	if (!directory)
	{
		node = find_key(*env, "HOME");
		chdir(node->value);
		temp = node->value;
		node = find_key(*env, "PWD");
		node->value = temp;
		return ;
	}
	if (!ft_strncmp(directory, ".", 2))
		return ;
	if (!ft_strncmp(directory, "-", 1))
	{
		node = find_key(*env, "HOME");
		temp = node->value;
		node = find_key(*env, "PWD");
		if (chdir(temp) == 0)
		{
			node->value = temp;
			write(STDOUT_FILENO, temp, ft_strlen(temp));
			write(STDOUT_FILENO, "\n", 1);
		}
		return ;
	}
	if (!ft_strncmp(directory, "..", 3))
	{
		i = 0;
		node = find_key(*env, "PWD");
		i = last_slash(node->value);
		temp = ft_strndup(node->value, i);
		if (chdir(temp) == 0)
		{
			ft_free(&node->value);
			node->value = ft_strdup(temp);
		}
		ft_free(&temp);
		return ;
	}
	if (directory[0] != '/')
		directory = ft_strjoin("/", directory);
	node = find_key(*env, "PWD");
	path = ft_strjoin(node->value, directory);
	if (chdir(path) == -1)
	{
		write(1, "cd: ", 4);
		write(1, directory, ft_strlen(directory));
		write(1, ": No such file or directory\n", 28);
		return ;
	}
	node->value = path;
}

void	absolute_path(t_env_ll **env, char *directory)
{
	t_env_ll	*node;

	if (chdir(directory) == 0)
	{
		node = find_key(*env, "PWD");
		ft_free(&node->value);
		node->value = ft_strdup(directory);
	}
	else
	{
		write(1, "cd: ", 4);
		write(1, directory, ft_strlen(directory));
		write(1, ": No such file or directory\n", 28);
	}
}

void	cd(t_env_ll **env, char *directory)
{
	if (!directory || directory[0] != '/')
		relative_path(env, directory);
	else
		absolute_path(env, directory);
}

// int	main(void)
// {
// 	cd("directory_test");
// 	return (0);
// }