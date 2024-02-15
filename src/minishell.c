/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/15 09:20:33 by rfinneru      ########   odam.nl         */
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
		dup2(STDOUT_FILENO, iostream->stdout_fd);
		dup2(STDIN_FILENO, iostream->stdin_fd);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execute(&command, iostream, true);
	}
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

	status = 0;
	pid = 1;
	if (!arg || !arg[0])
		return (0);
	malloc_stream(&iostream, env);
	command = NULL;
	init_redirections(arg, &command);
	total_pipes = pipe_check(command);
	wait_total = pipe_check(command) + 1;
	if (!total_pipes)
		no_pipes(command, iostream);
	else
	{
		while (total_pipes > 0)
		{
			init_stream(&iostream);
			init_pipe(iostream->pipes);
			until_pipe = get_command_until_pipe(command);
			command = get_command_from_pipe(command);
			// printf("%d\n", until_pipe->token);
			pid = fork();
			if (pid == 0)
				execute(&until_pipe, iostream, true);
			close(iostream->pipes->curr_write);
			total_pipes--;
		}
		close(iostream->pipes->curr_write);
		init_stream(&iostream);
		until_pipe = get_command_until_pipe(command);
		pid = fork();
		if (pid == 0)
			execute(&until_pipe, iostream, true);
	}
	while (wait_total)
	{
		wait(NULL);
		wait_total--;
	}
	if (total_pipes)
		close_pipes(iostream->pipes);
	return (check_status(status));
}
