/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing_utils4.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:58:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 09:17:31 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dir_check(char *argv)
{
	DIR	*p;

	p = opendir(argv);
	if (p)
	{
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, argv, ft_strlen(argv));
		write(STDOUT_FILENO, ": Is a directory\n", 17);
		closedir(p);
		exit(126);
	}
	else
		print_file_dir_err(argv, false);
	exit(127);
}

void	check_dir_exe(char *argv)
{
	if (!argv)
	{
		return ;
	}
	if (!ft_strncmp(argv, "/home", 5) || (argv[0] == '.' && argv[1] == '/'))
	{
		if (access(argv, F_OK) != 0)
		{
			print_file_dir_err(argv, false);
			exit(127);
		}
		else if (access(argv, X_OK) != 0)
		{
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, argv, ft_strlen(argv));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			exit(126);
		}
		dir_check(argv);
	}
}

int	length_command(char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (0);
	while (command[i])
		i++;
	return (i + 1);
}

char	*init_set_valid_command(char *argv, int *j, char **full_path)
{
	char	*trimmed_command;

	if (!argv || !argv[0])
		return (NULL);
	if (argv && !full_path)
	{
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
		else
			return (NULL);
	}
	if (!full_path)
		return (NULL);
	trimmed_command = ft_strdup(argv);
	if (!trimmed_command)
		return (NULL);
	*j = -1;
	return (trimmed_command);
}

char	*set_valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	char	*trimmed_command;
	char	*temp;

	trimmed_command = init_set_valid_command(argv, &j, full_path);
	if (!trimmed_command)
		return (NULL);
	if (access(argv, X_OK) == 0)
		return (free(trimmed_command), argv);
	while (full_path[++j])
	{
		temp = ft_strjoin(full_path[j], "/");
		if (!temp)
			return (ft_free(&trimmed_command), NULL);
		str = ft_strjoin(temp, trimmed_command);
		if (!str)
			return (ft_free(&temp), ft_free(&trimmed_command), NULL);
		if (access(str, X_OK) == 0)
			return (ft_free(&temp), str);
		ft_free2(&str, &temp);
	}
	ft_free(&trimmed_command);
	return (str);
}
