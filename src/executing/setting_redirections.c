/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setting_redirections.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 12:55:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/11 14:56:58 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	token_checker(t_command *command, t_stream *iostream)
{
	int	status;

	status = 0;
	if (command->token == RE_IN)
		status = redirection_in(iostream, command);
	else if (command->token == RE_OUT)
		status = redirection_out(iostream, command);
	else if (command->token == RE_APPEND)
		status = redirection_append(iostream, command);
	else if (command->token == RE_HERE)
		redirection_here(iostream, command);
	return (status);
}

int	setup_and_do_execute(t_command **param, t_stream *iostream, int *pid)
{
	signal(SIGINT, SIG_IGN);
	*pid = fork();
	if (*pid == -1)
		return (0);
	if (*pid == 0)
	{
		send_signals(RUNNING_CMD);
		if (execute(param, iostream) == -1)
			return (0);
	}
	if (iostream->input != -1)
	{
		if (close(iostream->input) == -1)
			return (0);
	}
	if (iostream->output != -1)
	{
		if (close(iostream->output) == -1)
			return (0);
	}
	return (1);
}

int	set_redirections(t_command **param, t_stream *iostream, bool child,
		int *pid)
{
	t_command	*command;
	int			status;

	command = *param;
	if (command->token == PIPE && last_node(&command->next))
		iostream->input = iostream->pipes->prev_read;
	else if (command->token == PIPE)
		iostream->input = iostream->pipes->curr_read;
	if (command->token == PIPE)
		command = command->next;
	while (command && command->token != PIPE)
	{
		status = token_checker(command, iostream);
		if (status)
		{
			printf("hre\n");
			return (1);
		}command = command->next;
	}
	if (command)
	{
		if (command->token == PIPE && iostream->output == -1)
			iostream->output = iostream->pipes->curr_write;
	}
	if (child == true)
		setup_and_do_execute(param, iostream, pid);
	return (0);
}
