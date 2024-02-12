/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 15:51:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/12 13:40:01 by rfinneru      ########   odam.nl         */
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
		free(temp);
		if (access(str, X_OK) == 0)
			return (1);
		free(str);
		j++;
	}
	free(trimmed_command);
	return (0);
}

char	*set_valid_command(char *argv, char **full_path)
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
	if (access(argv, X_OK) == 0)
		return (argv);
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (NULL);
		free(temp);
		if (access(str, X_OK) == 0)
			break ;
		free(str);
		j++;
	}
	free(trimmed_command);
	return (str);
}
