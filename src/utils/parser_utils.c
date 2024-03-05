/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:49:56 by rfinneru          #+#    #+#             */
/*   Updated: 2024/03/04 17:33:49 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_path(char **envp)
{
	int		i;
	char	*path_string;
	char	**result_string;

	path_string = NULL;
	i = 0;
	while (!path_string)
	{
		path_string = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	result_string = ft_split(path_string + 5, ':');
	if (!result_string)
		return (NULL);
	return (result_string);
}

t_command	*get_command_from_pipe(t_command *command)
{
	t_command	*head;

	head = command;
	// t_command *temp;
	if (head && head->token == PIPE)
	{
		// temp = head;
		head = head->next;
	}
	while (head && head->token != PIPE)
	{
		// temp = head;
		head = head->next;
	}
	return (head);
}

t_command	*get_command_until_pipe(t_command *command)
{
	t_command	*head;
	t_command	*current;

	head = NULL;
	if (command)
	{
		if (createnode(&head, command->string, command->token) == -1)
			return (NULL);
		command = command->next;
	}
	current = head;
	while (command && command->token != PIPE)
	{
		current = createnode_return(&head, command->string, command->token);
		if (!current)
			return (NULL);
		command = command->next;
		current = current->next;
	}
	if (command)
	{
		if (createnode(&head, command->string, command->token) == -1)
			return (NULL);
	}
	return (head);
}

int	pipe_check(t_command *command)
{
	int			total_pipes;
	t_command	*pointer;

	pointer = command;
	total_pipes = 0;
	while (pointer)
	{
		if (pointer->token == PIPE)
			total_pipes++;
		pointer = pointer->next;
	}
	return (total_pipes);
}
