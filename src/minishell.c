/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/28 11:19:04 by rfinneru      ########   odam.nl         */
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
	set_args(param, iostream, count);
	return (count);
}

int	no_pipes(t_command *command, t_stream *iostream, bool *exit_called)
{
	pid_t	pid;
	int		status;
	int		count;
	bool	builtin;

	builtin = false;
	status = 0;
	count = 0;
	pid = -1;
	init_stream(&iostream);
	if (command->token == BUILTIN && (ft_strncmp(command->string, "cd", 3) == 0
			|| (ft_strncmp(command->string, "export", 7) == 0)
			|| (ft_strncmp(command->string, "unset", 6) == 0)
			|| (ft_strncmp(command->string, "exit", 4)) == 0))
	{
		execute(&command, iostream, false, &pid);
		count = main_set_args(&command, iostream);
		if ((ft_strncmp(command->string, "exit", 4)) == 0)
		{
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
		}
		else
		{
			status = get_builtin(command->string, iostream, iostream->env);
			builtin = true;
		}
	}
	else
	{
		status = execute(&command, iostream, true, &pid);
		if (iostream->file_failure)
		{
			free_ll_command(command, true);
			free_iostream(&iostream, count);
			return (status);
		}
	}
	if (!builtin)
		waitpid(pid, &status, 0);
	free_ll_command(command, true);
	free_iostream(&iostream, count);
	if (builtin && !exit_called)
		return (status);
	else
		return (check_status(status));
}

int	init_command_line(t_env_ll **env, t_stream **iostream, t_command **command,
		char *arg)
{
	int	total;

	malloc_stream(iostream, env);
	*command = NULL;
	init_redirections(arg, command);
	total = pipe_check(*command);
	return (total);
}

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

int	command_line(t_env_ll **env, char *arg, int exit_status, bool *exit)
{
	t_command	*command;
	t_command	*until_pipe;
	t_command	*saved;
	t_stream	*iostream;
	int			total_pipes;
	pid_t		pid;
	int			wait_total;
	int			status;

	status = 0;
	pid = -1;
	if (!arg || !arg[0])
		return (0);
	total_pipes = init_command_line(env, &iostream, &command, arg);
	iostream->prev_exit_status = exit_status;
	saved = command;
	wait_total = total_pipes + 1;
	if (!total_pipes)
		return (no_pipes(command, iostream, exit));
	else
	{
		while (total_pipes > 0)
		{
			init_stream(&iostream);
			init_pipe(iostream->pipes);
			until_pipe = get_command_until_pipe(command);
			command = get_command_from_pipe(command);
			execute(&until_pipe, iostream, true, &pid);
			close(iostream->pipes->curr_write);
			total_pipes--;
			free_ll_command(until_pipe, false);
		}
		close(iostream->pipes->curr_write);
		init_stream(&iostream);
		until_pipe = get_command_until_pipe(command);
		status = execute(&until_pipe, iostream, true, &pid);
		if (iostream->file_failure)
		{
			free_all_close_pipes(saved, until_pipe, iostream, total_pipes);
			return (status);
		}
	}
	status = wait_for_processes(pid, wait_total);
	free_all_close_pipes(saved, until_pipe, iostream, total_pipes);
	return (check_status(status));
}
