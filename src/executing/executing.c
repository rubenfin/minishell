/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 12:55:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 16:27:41 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirection_in(t_stream *iostream, t_command *command)
{
	iostream->input = open(command->string, O_RDONLY);
}

void	redirection_out(t_stream *iostream, t_command *command)
{
	iostream->output = open(command->string, O_CREAT | O_WRONLY | O_TRUNC,
			0644);
}

void	redirection_append(t_stream *iostream, t_command *command)
{
	iostream->output = open(command->string, O_WRONLY | O_CREAT | O_APPEND,
			0644);
}

int	last_node(t_command **param)
{
	t_command	*command;

	command = *param;
	while (command)
	{
		if (command->token == PIPE)
			return (1);
		command = command->next;
	}
	return (0);
}

void	execute(t_command **param, t_stream *iostream)
{
	t_command	*command;

	command = *param;
	if (command->token == PIPE && last_node(&command->next))
		iostream->input = iostream->pipes->prev_read;
	else if (command->token == PIPE)
		iostream->input = iostream->pipes->curr_read;
	if (command->token == PIPE)
		command = command->next;
	while (command && command->token != PIPE)
	{
		if (command->token == RE_IN)
			redirection_in(iostream, command);
		else if (command->token == RE_OUT)
			redirection_out(iostream, command);
		else if (command->token == RE_APPEND)
			redirection_append(iostream, command);
		command = command->next;
	}
	if (command)
	{
		if (command->token == PIPE && iostream->output == -1)
			iostream->output = iostream->pipes->curr_write;
	}
	execute_single(param, iostream);
}