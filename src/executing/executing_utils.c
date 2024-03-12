/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 15:04:48 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/11 15:12:52 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_processes(int pid, int wait_total)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (!wait_total)
		return (0);
	else
	{
		while (wait_total - 1)
		{
			wait(NULL);
			wait_total--;
		}
	}
	return (status);
}

int	setup_cmds(t_cmd_data **data, t_command **command)
{
	(*data) = (t_cmd_data *)malloc(sizeof(t_cmd_data));
	if (!(*data))
		return (0);
	(*data)->command = command;
	(*data)->total_pipes = pipe_check(*(*data)->command);
	(*data)->wait_total = (*data)->total_pipes + 1;
	if (!(*data)->total_pipes)
		return (1);
	(*data)->one_cmd = *command;
	(*data)->cmds_left = *command;
	return (1);
}

int	setup_before_executing(t_cmd_data **data, t_env_ll **env,
		t_command **command, t_stream **iostream)
{
	if (!setup_cmds(data, command))
		return (0);
	if (!malloc_stream(iostream, env))
		return (0);
	return (1);
}

int	trim_command(t_cmd_data **data, bool last_cmd)
{
	(*data)->one_cmd = get_command_until_pipe((*data)->cmds_left);
	if (!(*data)->one_cmd)
		return (0);
	if (!last_cmd)
	{
		(*data)->cmds_left = get_command_from_pipe((*data)->cmds_left);
		if (!(*data)->cmds_left)
			return (0);
	}
	return (1);
}

int	clean_cmd_leftovers(t_cmd_data **data, t_stream **iostream)
{
	if ((*iostream)->pipes->curr_write)
		close((*iostream)->pipes->curr_write);
	free_ll_command((*data)->one_cmd, false);
	return (1);
}
