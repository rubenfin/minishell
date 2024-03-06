/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 18:16:08 by rfinneru      ########   odam.nl         */
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

int	do_exit(t_stream *iostream, bool *exit_called)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = -1;
	if (check_if_valid_exit(iostream->args))
		*exit_called = true;
	pid = fork();
	if (pid == 0)
	{
		status = get_exit(*iostream->env, iostream->args);
		exit(status);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}
int	check_parent_builtin(char *str)
{
	if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	else
		return (0);
}

void	clean_single_cmd(cmd_data *data, t_stream *iostream, int count)
{
	free_ll_command(*data->command, true);
	free_iostream(&iostream, count);
	free(data);
}

int	setup_builtin_no_pipes(t_command **command, t_stream *iostream, int *pid,
		int *count)
{
	set_redirections(command, iostream, false, pid);
	*count = main_set_args(command, iostream);
	if (*count == -1)
		return (0);
	return (1);
}
int	no_pipes(cmd_data **data, t_stream *iostream, bool *exit_called)
{
	pid_t		pid;
	int			status;
	int			count;
	t_command	*command;

	command = *(*data)->command;
	status = 0;
	count = 0;
	pid = -1;
	init_stream(&iostream);
	if (command->token == BUILTIN && check_parent_builtin(command->string))
	{
		setup_builtin_no_pipes(&command, iostream, &pid, &count);
		if ((ft_strncmp(command->string, "exit", 4)) == 0)
			status = do_exit(iostream, exit_called);
		else
			status = get_builtin(command->string, iostream, iostream->env);
	}
	else
	{
		status = set_redirections(&command, iostream, true, &pid);
		if (iostream->file_failure)
			return (clean_single_cmd(*data, iostream, count), status);
		else
			waitpid(pid, &status, 0);
	}
	clean_single_cmd(*data, iostream, count);
	if (pid != -1 || *exit_called)
		return (check_status(status));
	else
		return (status);
}

int	command_line(t_env_ll **env, t_command **parsed, bool *exit)
{
	cmd_data	*data;
	t_stream	*iostream;
	pid_t		pid;
	int			status;

	data = NULL;
	status = 0;
	pid = -1;
	if (!setup_before_executing(&data, env, parsed, &iostream))
		return (-1);
	if (!data->total_pipes)
		return (no_pipes(&data, iostream, exit));
	while (data->total_pipes-- > 0)
	{
		init_stream_pipes(&iostream);
		trim_command(&data, false);
		set_redirections(&data->one_cmd, iostream, true, &pid);
		clean_cmd_leftovers(&data, &iostream);
	}
	setup_last_cmd(&data, &iostream);
	status = set_redirections(&data->one_cmd, iostream, true, &pid);
	status_and_clean(&data, &iostream, &status, &pid);
	return (check_status(status));
}
