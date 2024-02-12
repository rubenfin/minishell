/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/12 18:35:36 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env_ll	*env;
	char		*arg;
	t_command	*command;
	t_command	*until_pipe;
	t_stream	*iostream;
	int			total_pipes;
	pid_t		pid;
	int			wait_total;
	int			status;
	int			x;

	make_env_ll(&env, envp);
	status = 0;
	pid = 1;
	(void)argc;
	(void)argv;
	malloc_stream(&iostream, envp);
	arg = "cat < infile < outfile";
	x = 0;
	command = NULL;
	init_redirections(arg, &command);
	total_pipes = pipe_check(command);
	wait_total = pipe_check(command) + 1;
	if (!total_pipes)
	{
		init_stream(&iostream);
		pid = fork();
		if (pid == 0)
			execute(&command, iostream);
	}
	if (total_pipes)
	{
		while (total_pipes > 0)
		{
			init_stream(&iostream);
			init_pipe(iostream->pipes);
			until_pipe = get_command_until_pipe(command);
			command = get_command_from_pipe(command);
			pid = fork();
			if (pid == 0)
				execute(&until_pipe, iostream);
			close(iostream->pipes->curr_write);
			total_pipes--;
		}
		until_pipe = get_command_until_pipe(command);
		command = get_command_from_pipe(command);
		pid = fork();
		if (pid == 0)
			execute(&until_pipe, iostream);
	}
	while (wait_total--)
		wait(NULL);
	waitpid(pid, &status, 0);
	return (check_status(status));
}
