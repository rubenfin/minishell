/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 16:36:54 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/02/12 13:39:46 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_command **param)
{
	int			count;
	t_command	*command;

	count = 0;
	command = *param;
	while (command && command->token != PIPE)
	{
		if (command->token == CMD)
			count++;
		command = command->next;
	}
	return (count);
}

void	set_args(t_command **param, t_stream *iostream, int count)
{
	int			i;
	t_command	*command;

	i = 0;
	command = *param;
	if (command->token == PIPE)
		command = command->next;
	while (i < count)
	{
		if (command->token == CMD)
			iostream->args[i] = ft_strdup(command->string);
		command = command->next;
		++i;
	}
	iostream->args[i] = NULL;
}

void	execute_single(t_command **param, t_stream *iostream)
{
	t_command *command;
	int count;

	command = *param;
	if (command->token == PIPE)
		command = command->next;
	count = count_commands(&command);
	iostream->args = (char **)malloc(sizeof(char *) * count);
	set_args(param, iostream, count);
	if (iostream->input != -1)
		dup2(iostream->input, STDIN_FILENO);
	if (iostream->output != -1)
		dup2(iostream->output, STDOUT_FILENO);
	execve(set_valid_command(iostream->args[0], iostream->PATH), iostream->args,
		iostream->PATH);
	perror("did not execute");
	exit(0);
}