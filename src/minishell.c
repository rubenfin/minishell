/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/11 12:43:22 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main_set_args(t_command **param, t_stream *iostream)
{
	t_command	*command;
	int			count;

	command = *param;
	if (command->token == PIPE)
		command = command->next;
	count = count_commands(&command);
	iostream->args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!iostream->args)
		return (-1);
	set_args(param, iostream, count);
	return (count);
}

int	setup_builtin_no_pipes(t_command **command, t_stream *iostream, int *pid,
		int *count)
{
	set_redirections(command, iostream, false, pid);
	*count = main_set_args(command, iostream);
	if (iostream->file_failure)
		return (0);
	if (*count == -1)
		return (0);
	return (1);
}

int	builtin(t_cmd_data *data, t_stream *iostream, bool *exit_called)
{
	pid_t		pid;
	int			status;
	t_command	*command;
	int			count;

	command = *(data)->command;
	count = 0;
	status = 0;
	pid = -1;
	if (!setup_builtin_no_pipes(&command, iostream, &pid, &count))
		return (clean_single_cmd(data, iostream, count), -1);
	if ((ft_strncmp(command->string, "exit", 4)) == 0)
		status = do_exit(iostream, exit_called);
	else
		status = get_builtin(command->string, iostream, iostream->env);
	clean_single_cmd(data, iostream, count);
	return (return_right_status(exit_called, pid, status));
}

int	no_pipes(t_cmd_data *data, t_stream *iostream, bool *exit_called)
{
	pid_t		pid;
	int			status;
	int			count;
	t_command	*command;

	command = *(data)->command;
	status = 0;
	count = 0;
	pid = -1;
	init_stream(&iostream);
	if (command->token == BUILTIN && check_parent_builtin(command->string))
		return (builtin(data, iostream, exit_called));
	else
	{
		status = set_redirections(&command, iostream, true, &pid);
		if (iostream->file_failure)
			return (clean_single_cmd(data, iostream, count), status);
		else
			waitpid(pid, &status, 0);
	}
	// clean_single_cmd(data, iostream, count);
	return (return_right_status(exit_called, pid, status));
}

int	command_line(t_env_ll **env, t_command **parsed, bool *exit)
{
	t_cmd_data	*data;
	t_stream	*iostream;
	pid_t		pid;
	int			status;

	data = NULL;
	status = 0;
	pid = -1;
	if (!setup_before_executing(&data, env, parsed, &iostream))
		return (-1);
	if (!data->total_pipes)
		return (no_pipes(data, iostream, exit));
	while (data->total_pipes-- > 0)
	{
		if (!init_stream_pipes(&iostream))
			return (clean_all(&data, iostream, data->total_pipes), -1);
		if (!trim_command(&data, false))
			return (clean_all(&data, iostream, data->total_pipes), -1);
		if (set_redirections(&data->one_cmd, iostream, true, &pid))
			return (clean_all(&data, iostream, data->total_pipes), -1);
		clean_cmd_leftovers(&data, &iostream);
	}
	setup_last_cmd(&data, &iostream);
	status = set_redirections(&data->one_cmd, iostream, true, &pid);
	return (status_and_clean(&data, &iostream, &status, &pid));
}
