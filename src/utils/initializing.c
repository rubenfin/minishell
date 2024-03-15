/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 16:17:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/15 10:54:40 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	malloc_stream(t_stream **iostream, t_env_ll **env)
{
	(*iostream) = (t_stream *)malloc(sizeof(t_stream));
	if (!(*iostream))
		return (0);
	(*iostream)->env = env;
	(*iostream)->pipes = (t_pipes *)malloc(sizeof(t_pipes));
	if (!((*iostream)->pipes))
		return (0);
	(*iostream)->pipes->curr_read = 0;
	(*iostream)->pipes->curr_write = 0;
	(*iostream)->pipes->prev_read = 0;
	(*iostream)->pipes->prev_write = 0;
	return (1);
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
		return (0);
	pipes->curr_write = fds[1];
	pipes->curr_read = fds[0];
	return (1);
}

void	init_stream(t_stream **iostream)
{
	g_signal_status = -1;
	(*iostream)->args = NULL;
	(*iostream)->input = -1;
	(*iostream)->output = -1;
	(*iostream)->file_failure = false;
	(*iostream)->pipe = false;
}

int	init_stream_pipes(t_stream **iostream)
{
	init_stream(iostream);
	if (!init_pipe((*iostream)->pipes))
		return (0);
	(*iostream)->pipe = true;
	return (1);
}

int	init_std_fd(t_std_fd **std_fd)
{
	(*std_fd) = (t_std_fd *)malloc(sizeof(t_std_fd));
	if (!(*std_fd))
		return (0);
	(*std_fd)->stdin_fd = dup(STDIN_FILENO);
	if ((*std_fd)->stdin_fd == -1)
		return (0);
	(*std_fd)->stdout_fd = dup(STDOUT_FILENO);
	if ((*std_fd)->stdout_fd == -1)
		return (0);
	(*std_fd)->stderr_fd = dup(STDERR_FILENO);
	if ((*std_fd)->stderr_fd == -1)
		return (0);
	return (1);
}
