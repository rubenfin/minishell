/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 15:49:56 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 15:58:02 by rfinneru      ########   odam.nl         */
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
