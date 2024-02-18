/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/18 10:00:15 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_set_args(t_command **param, t_stream *iostream)
{
	t_command	*command;
	int			count;

	command = *param;
	if (command->token == PIPE)
		command = command->next;
	count = count_commands(&command);
	iostream->args = (char **)malloc(sizeof(char *) * count);
	set_args(param, iostream, count);
}

int	no_pipes(t_command *command, t_stream *iostream)
{
	pid_t	pid;
	int		status;

	pid = 1;
	init_stream(&iostream);
	if (command->token == BUILTIN && (ft_strncmp(command->string, "cd", 3) == 0
			|| (ft_strncmp(command->string, "export", 7) == 0)
			|| (ft_strncmp(command->string, "unset", 6) == 0)
			|| (ft_strncmp(command->string, "exit", 5)) == 0))
	{
		execute(&command, iostream, false);
		main_set_args(&command, iostream);
		get_builtin(command->string, iostream, iostream->env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execute(&command, iostream, true);
		else
			waitpid(pid, &status, 0);
	}
	free_ll_command(command, true);
	free(iostream->pipes);
	free(iostream);
	return (status);
}

int	init_command_line(t_env_ll *env, t_stream **iostream, t_command **command,
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
	return (waitpid(pid, &status, 0));
}

int	command_line(t_env_ll *env, char *arg)
{
	t_command	*command;
	t_command	*until_pipe;
	t_stream	*iostream;
	int			total_pipes;
	pid_t		pid;
	int			wait_total;
	int			status;
	t_command	*saved;

	pid = 1;
	if (!arg || !arg[0])
		return (0);
	total_pipes = init_command_line(env, &iostream, &command, arg);
	saved = command;
	wait_total = total_pipes + 1;
	if (!total_pipes)
		return (check_status(no_pipes(command, iostream)));
	else
	{
		while (total_pipes > 0)
		{
			init_stream(&iostream);
			init_pipe(iostream->pipes);
			until_pipe = get_command_until_pipe(command);
			command = get_command_from_pipe(command);
			pid = fork();
			if (pid == 0)
				execute(&until_pipe, iostream, true);
			close(iostream->pipes->curr_write);
			total_pipes--;
			free_ll_command(until_pipe,false);
		}
		close(iostream->pipes->curr_write);
		init_stream(&iostream);
		until_pipe = get_command_until_pipe(command);
		pid = fork();
		if (pid == 0)
			execute(&until_pipe, iostream, true);
	}
	free_ll_command(until_pipe, false);
	free_ll_command(saved, true);
	status = wait_for_processes(pid, wait_total);
	if (total_pipes)
		close_pipes(iostream->pipes);
	free(iostream->pipes);
	free(iostream);
	return (check_status(status));
}
