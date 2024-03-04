/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 15:49:56 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/04 15:58:30 by rfinneru      ########   odam.nl         */
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
	while (envp[i] && !path_string)
	{
		path_string = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	if (!path_string)
		return(NULL);
	result_string = ft_split(path_string + 5, ':');
	if (!result_string)
		return(NULL);
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
		createnode(&head, command->string, command->token);
		command = command->next;
	}
	current = head;
	while (command && command->token != PIPE)
	{
		current = createnode(&head, command->string, command->token);
		command = command->next;
		current = current->next;
	}
	if (command)
		createnode(&head, command->string, command->token);
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
