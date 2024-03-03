/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 15:51:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/01 21:04:55 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*createnode(t_command **head, char *data, int redirection)
{
	t_command	*newnode;
	t_command	*temp;

	newnode = (t_command *)malloc(sizeof(t_command));
	if (!newnode)
		return (NULL);
	newnode->string = data;
	newnode->token = redirection;
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (newnode);
}

int	length_command(char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (0);
	while (command[i] && command[i] != ' ')
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
	if (argv[0] == '/')
		dir_check(argv);
	else if ((argv[0] == '.' && argv[1] == '/'))
	{
		if (access(argv, F_OK) != 0)
		{
			print_file_dir_err(argv, false);
			exit(127);
		}
		else if (access(argv, X_OK) != 0)
		{
			printf("minishell: filename: Permission denied\n");
			exit(126);
		}
		dir_check(argv);
	}
}
char	*set_valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed_command)
		return (0);
	ft_strlcpy(trimmed_command, argv, len);
	trimmed_command[len] = '\0';
	j = 0;
	if (!argv[0])
		return (free(trimmed_command), NULL);
	if (access(argv, X_OK) == 0)
		return (argv);
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
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
