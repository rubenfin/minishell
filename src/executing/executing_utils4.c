/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing_utils4.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:58:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 13:49:24 by rfinneru      ########   odam.nl         */
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

int	valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc(len * sizeof(char));
	if (!trimmed_command)
		return (0);
	ft_strlcpy(trimmed_command, argv, len);
	j = 0;
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (0);
		ft_free(&temp);
		if (access(str, X_OK) == 0)
			return (1);
		ft_free(&str);
		j++;
	}
	ft_free(&trimmed_command);
	return (0);
}

char	*set_valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	if (!argv)
		return (NULL);
	len = length_command(argv);
	trimmed_command = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed_command)
		return (NULL);
	ft_strlcpy(trimmed_command, argv, len);
	trimmed_command[len] = '\0';
	j = 0;
	if (!argv[0])
		return (free(trimmed_command), NULL);
	if (access(argv, X_OK) == 0)
		return (free(trimmed_command), argv);
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		if (!temp)
			return (NULL);
		str = ft_strjoin(temp, trimmed_command);
		if (!str)
			return (NULL);
		ft_free(&temp);
		if (access(str, X_OK) == 0)
			return (str);
		ft_free(&str);
		j++;
	}
	ft_free(&trimmed_command);
	if (!str)
		return (NULL);
	return (str);
}