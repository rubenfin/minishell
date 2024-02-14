/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:04:05 by rfinneru          #+#    #+#             */
/*   Updated: 2024/02/14 12:24:01 by jade-haa         ###   ########.fr       */
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

	// new_stdout_fd = dup(STDOUT_FILENO);
	make_env_ll(&env, envp);
	// print_list_env(env);
	status = 0;
	pid = 1;
	(void)argc;
	(void)argv;
	malloc_stream(&iostream, env);
	arg = "env | grep a > outfile";
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
			printf("%d\n", until_pipe->token);
			if (until_pipe->token != BUILTIN)
			{
				pid = fork();
				if (pid == 0)
					execute(&until_pipe, iostream);
			}
			else
				execute(&until_pipe, iostream);
			close(iostream->pipes->curr_write);
			total_pipes--;
		}
		init_stream(&iostream);
		until_pipe = get_command_until_pipe(command);
		command = get_command_from_pipe(command);
		if (until_pipe->token != BUILTIN)
		{
			pid = fork();
			if (pid == 0)
				execute(&until_pipe, iostream);
		}
		else
			execute(&until_pipe, iostream);
	}
	while (wait_total--)
		wait(NULL);
	return (check_status(status));
}
