/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:04:05 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 16:06:00 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}

int	pipe_check(t_command *command)
{
	int			total_pipes;
	t_command	*pointer;

	pointer = command;
	total_pipes = 0;
	while (pointer)
	{
		if (pointer->token == PIPE)
			total_pipes++;
		pointer = pointer->next;
	}
	return (total_pipes);
}

int	init_pipe(t_pipes *pipes)
{
	int	fds[2];

	if (pipes->curr_write)
	{
		pipes->prev_write = pipes->curr_write;
		pipes->prev_read = pipes->curr_read;
	}
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pipes->curr_write = fds[1];
	pipes->curr_read = fds[0];
	return (0);
}

void	init_stream(t_stream **iostream)
{
	(*iostream)->args = NULL;
	(*iostream)->input = -1;
	(*iostream)->output = -1;
}

t_command	*get_command_from_pipe(t_command *command)
{
	t_command	*head;

	head = command;
	if (head && head->token == PIPE)
		head = head->next;
	while (head && head->token != PIPE)
		head = head->next;
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	char		*arg;
	int			i;
	t_command	*command;
	t_command	*until_pipe;
	t_stream	*iostream;
	int			total_pipes;
	pid_t		pid;
	int			wait_total;
	int			forked;
	int			status;

	status = 0;
	pid = 4389;
	i = 0;
	(void)argv;
	(void)argc;
	(void)envp;
	if (argc < 2)
		return (printf("only 1 arg"), 0);
	iostream = (t_stream *)malloc(sizeof(t_stream));
	iostream->PATH = get_path(envp);
	iostream->pipes = (t_pipes *)malloc(sizeof(t_pipes));
	arg = argv[1];
	command = NULL;
	init_redirections(arg, &command);
	total_pipes = pipe_check(command);
	wait_total = pipe_check(command) + 1;
	forked = 0;
	if (!total_pipes)
	{
		pid = fork();
		if (pid == 0)
		{
			init_stream(&iostream);
			execute(&command, iostream);
		}
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
			;
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
	while (--wait_total)
		wait_total--;
	waitpid(pid, &status, 0);
	return (check_status(status));
}
