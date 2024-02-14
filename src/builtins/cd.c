/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 12:09:22 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/14 17:03:25 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	last_slash(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '/')
			x = i;
		i++;
	}
	return (x);
}

void	cd(t_env_ll *env, char *directory)
{
	t_env_ll	*node;
	char		*path;
	char		*temp;
	int			i;

	// add absolute path
	if (!directory)
	{
		node = find_key(env, "HOME=");
		chdir(node->value);
		temp = node->value;
		node = find_key(env, "PWD=");
		node->value = temp;
		return ;
	}
	if (!ft_strncmp(directory, "..", 3))
	{
		i = 0;
		node = find_key(env, "PWD=");
		i = last_slash(node->value);
		temp = ft_strndup(node->value, i);
		if (chdir(temp) == 0)
			node->value = temp;
		return ;
	}
	if (directory[0] != '/')
		directory = ft_strjoin("/", directory);
	node = find_key(env, "PWD=");
	path = ft_strjoin(node->value, directory);
	if (chdir(path) == -1)
	{
		write(1, "cd: not a directory: ", 21);
		write(1, directory, ft_strlen(directory));
		write(1, "\n", 1);
		return ;
	}
	node->value = path;
}

// int	main(void)
// {
// 	cd("directory_test");
// 	return (0);
// }