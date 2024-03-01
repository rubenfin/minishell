/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 12:09:22 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/01 19:59:22 by rfinneru      ########   odam.nl         */
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
		return (1);
	return (x);
}

int	relative_path(t_env_ll **env, char *directory)
{
	t_env_ll	*node;
	char		*path;
	char		*temp;
	int			i;

	temp = NULL;
	if (!directory)
	{
		if (chdir(find_key_return_value(*env, "HOME")) == -1)
		{
			write(STDOUT_FILENO, "cd: HOME not set\n", 17);
			return (1);
		}
		find_key_free_value(env, "OLDPWD");
		temp = find_key_return_value(*env, "PWD");
		get_key_change_value(env, "OLDPWD", temp);
		get_key_change_value(env, "PWD", ft_strdup(find_key_return_value(*env,
					"HOME")));
		return (0);
	}
	if (!ft_strncmp(directory, ".", 2) || !ft_strncmp(directory, "./", 2))
		return (0);
	if (!ft_strncmp(directory, "-", 1))
	{
		if (chdir(find_key_return_value(*env, "OLDPWD")) == 0)
		{
			temp = find_key_return_value(*env, "PWD");
			get_key_change_value(env, "PWD", find_key_return_value(*env,
					"OLDPWD"));
			get_key_change_value(env, "OLDPWD", temp);
			return (0);
		}
		return (1);
	}
	if (!ft_strncmp(directory, "..", 3))
	{
		i = 0;
		i = last_slash(find_key_return_value(*env, "PWD"));
		temp = ft_strndup(find_key_return_value(*env, "PWD"), i);
		if (chdir(temp) == 0)
		{
			change_pwd(env, temp);
			return (0);
		}
		else
			ft_free(&temp);
		return (1);
	}
	if (directory[0] != '/')
		directory = ft_strjoin("/", directory);
	node = find_key(*env, "PWD");
	path = ft_strjoin(node->value, directory);
	if (chdir(path) == -1)
	{
		print_file_dir_err(directory, true);
		ft_free(&directory);
		ft_free(&path);
		return (1);
	}
	ft_free(&directory);
	change_pwd(env, path);
	return (0);
}
char	*removed_slash_back(char *dir)
{
	char	*clean_dir;
	int		i;

	i = ft_strlen(dir);
	if (dir[i] != '/')
		return (ft_strndup(dir, i));
	while (i > 0)
	{
		if (dir[i] == '/' && (!dir[i - 1] || ft_isalnum(dir[i - 1])))
			break ;
		i--;
	}
	if (i == 0)
		return (ft_strdup("/"));
	clean_dir = ft_strndup(dir, i);
	return (clean_dir);
}

char	*removed_slash_infront(char *dir)
{
	char	*clean_dir;
	int		i;

	i = 0;
	while (dir[i])
	{
		if (dir[i] == '/' && (!dir[i + 1] || ft_isalnum(dir[i + 1])))
			break ;
		i++;
	}
	clean_dir = ft_strdup(dir + i);
	return (clean_dir);
}

int	absolute_path(t_env_ll **env, char *directory)
{
	char	*dir_no_slash;
	char	*temp;

	dir_no_slash = removed_slash_back(directory);
	if (chdir(directory) == 0)
	{
		temp = removed_slash_infront(dir_no_slash);
		change_pwd(env, temp);
	}
	else
	{
		print_file_dir_err(directory, true);
		ft_free(&dir_no_slash);
		return (1);
	}
	ft_free(&dir_no_slash);
	return (0);
}

int	cd(t_env_ll **env, char **directory)
{
	int	count;

	count = 0;
	while (directory[count])
		count++;
	if (count > 1)
		return (write(STDERR_FILENO, "minishell: cd: too many arguments\n",
				34), 1);
	if (!directory[0] || directory[0][0] != '/')
		return (relative_path(env, directory[0]));
	else
		return (absolute_path(env, directory[0]));
}

// int	main(void)
// {
// 	cd("directory_test");
// 	return (0);
// }