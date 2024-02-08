/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 15:49:56 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 16:20:32 by rfinneru      ########   odam.nl         */
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
