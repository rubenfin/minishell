/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:55:18 by rfinneru          #+#    #+#             */
/*   Updated: 2024/03/04 16:29:36 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/minishell.h"

int	redirection_here(t_stream *iostream, t_command *command)
{
	char	*limiter;
	char	*buffer;
	char	*str;
	int		fd;

	buffer = NULL;
	str = ft_strdup("");
	limiter = ft_strjoin(command->string, "\n");
	fd = open("objs/utils/.hd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (set_file_failure_return(iostream));
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer || !ft_strncmp(buffer, limiter, ft_strlen(limiter)))
		{
			ft_free(&buffer);
			break ;
		}
		str = ft_strjoin_gnl(str, buffer);
		ft_free(&buffer);
		if (!str)
		{
			ft_free(&limiter);
			return (EXIT_FAILURE);
		}
	}
	write(fd, str, ft_strlen(str));
	close(fd);
	iostream->input = open("objs/utils/.hd", O_RDONLY);
	ft_free(&str);
	ft_free(&limiter);
	return (EXIT_SUCCESS);
}

int	redirection_in(t_stream *iostream, t_command *command)
{
	if (access(command->string, F_OK) == -1 || access(command->string, R_OK) ==
		-1)
	{
		print_file_dir_err(command->string, false);
		return (set_file_failure_return(iostream));
	}
	iostream->input = open(command->string, O_RDONLY);
	if (iostream->input == -1)
	{
		print_file_dir_err(command->string, false);
		return (set_file_failure_return(iostream));
	}
	return (EXIT_SUCCESS);
}

int	redirection_out(t_stream *iostream, t_command *command)
{
	if (access(command->string, F_OK) == 0 && access(command->string, W_OK) ==
		-1)
	{
		printf("here\n");
		print_file_dir_err(command->string, false);
		return (set_file_failure_return(iostream));
	}
	iostream->output = open(command->string, O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (iostream->output == -1)
	{
		print_file_dir_err(command->string, false);
		return (set_file_failure_return(iostream));
	}
	return (EXIT_SUCCESS);
}

int	redirection_append(t_stream *iostream, t_command *command)
{
	if (access(command->string, F_OK) == 0 && access(command->string, W_OK) ==
		-1)
	{
		print_file_dir_err(command->string, false);
		return (set_file_failure_return(iostream));
	}
	iostream->output = open(command->string, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (iostream->output == -1)
	{
		print_file_dir_err(command->string, false);
		return (set_file_failure_return(iostream));
	}
	return (EXIT_SUCCESS);
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

int	execute(t_command **param, t_stream *iostream, bool child, int *pid)
{
	t_command	*command;
	int			status;

	status = 0;
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
		{
			status = redirection_in(iostream, command);
			if (status)
				return (status);
		}
		else if (command->token == RE_OUT)
		{
			status = redirection_out(iostream, command);
			if (status)
				return (status);
		}
		else if (command->token == RE_APPEND)
		{
			status = redirection_append(iostream, command);
			if (status)
				return (status);
		}
		else if (command->token == RE_HERE)
		{
			redirection_here(iostream, command);
			if (status)
				return (status);
		}
		command = command->next;
	}
	if (command)
	{
		if (command->token == PIPE && iostream->output == -1)
			iostream->output = iostream->pipes->curr_write;
	}
	if (child == true)
	{
		*pid = fork();
		if (*pid == 0)
		{
			if (execute_single(param, iostream) == -1)
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}
