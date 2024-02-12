/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/06 12:55:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/12 18:38:29 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/minishell.h"

void	redirection_here(t_stream *iostream, t_command *command)
{
	char	*limiter;
	char	*buffer;
	char	*str;
	int		fd;
	pid_t	pid;

	buffer = NULL;
	pid = fork();
	if (pid == 0)
	{
		str = ft_strdup("");
		limiter = ft_strjoin(command->string, "\n");
		fd = open("objs/utils/.hd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			printf("failed to open");
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			buffer = get_next_line(STDIN_FILENO);
			if (!ft_strncmp(buffer, limiter, ft_strlen(limiter)))
			{
				free(buffer);
				break ;
			}
			str = ft_strjoin(str, buffer);
			free(buffer);
			buffer = NULL;
		}
		write(fd, str, ft_strlen(str));
		close(fd);
		iostream->input = open("objs/utils/.hd", O_RDONLY);
	}
	else if (pid > 0)
	{
		wait(NULL);
		unlink("objs/utils/.hd");
		exit(0);
	}
}

void	redirection_in(t_stream *iostream, t_command *command)
{
	if (access(command->string, F_OK) == -1 || access(command->string, R_OK) == -1)
	{
		write(STDIN_FILENO, "bash: ", 6);
		write(STDIN_FILENO, command->string, ft_strlen(command->string));
		write(STDIN_FILENO, ": ", 2);
		perror("");
		exit(EXIT_FAILURE);
	}
	iostream->input = open(command->string, O_RDONLY);
}

void	redirection_out(t_stream *iostream, t_command *command)
{
	iostream->output = open(command->string, O_CREAT | O_WRONLY | O_TRUNC,
			0644);
}

void	redirection_append(t_stream *iostream, t_command *command)
{
	iostream->output = open(command->string, O_WRONLY | O_CREAT | O_APPEND,
			0644);
}

int	last_node(t_command **param)
{
	t_command	*command;

	command = *param;
	while (command)
	{
		if (command->token == PIPE)
			return (1);
		command = command->next;
	}
	return (0);
}

void	execute(t_command **param, t_stream *iostream)
{
	t_command	*command;

	command = *param;
	if (command->token == PIPE && last_node(&command->next))
		iostream->input = iostream->pipes->prev_read;
	else if (command->token == PIPE)
		iostream->input = iostream->pipes->curr_read;
	if (command->token == PIPE)
		command = command->next;
	while (command && command->token != PIPE)
	{
		if (command->token == RE_IN)
			redirection_in(iostream, command);
		else if (command->token == RE_OUT)
			redirection_out(iostream, command);
		else if (command->token == RE_APPEND)
			redirection_append(iostream, command);
		else if (command->token == RE_HERE)
			redirection_here(iostream, command);
		command = command->next;
	}
	if (command)
	{
		if (command->token == PIPE && iostream->output == -1)
			iostream->output = iostream->pipes->curr_write;
	}
	execute_single(param, iostream);
}
