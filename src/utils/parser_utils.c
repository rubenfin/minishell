/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 15:49:56 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/09 09:46:27 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_list(t_command *command)
{
	t_command	*print;

	print = command;
	while (print)
	{
		printf("command: %s\n", print->string);
		printf("Token : %d\n\n", print->token);
		print = print->next;
	}
}

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
	result_string = ft_split(path_string, ':');
	if (!result_string)
		exit(1);
	return (result_string);
}

t_command	*get_command_from_pipe(t_command *command)
{
	t_command	*head;

	head = command;
	if (head && head->token == PIPE)
		head = head->next;
	while (head && head->token != PIPE)
		head = head->next;
	return (head);
}

t_command	*get_command_until_pipe(t_command *command)
{
	t_command	*head;
	t_command	*current;

	head = (t_command *)malloc(sizeof(t_command));
	if (command)
	{
		head = createnode(&head, command->string, command->token);
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
		current = createnode(&head, command->string, command->token);
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
