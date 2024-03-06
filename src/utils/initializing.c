/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 16:17:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 12:16:00 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	malloc_stream(t_stream **iostream, t_env_ll **env, int exit_status)
{
	(*iostream) = (t_stream *)malloc(sizeof(t_stream));
	if (!(*iostream))
		return (0);
	(*iostream)->env = env;
	(*iostream)->pipes = (t_pipes *)malloc(sizeof(t_pipes));
	if (!((*iostream)->pipes))
		return (0);
	(*iostream)->prev_exit_status = exit_status;
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
	(*iostream)->file_failure = false;
}

int	init_std_fd(t_std_fd **std_fd)
{
	(*std_fd) = (t_std_fd *)malloc(sizeof(t_std_fd));
	if (!(*std_fd))
		return (-1);
	(*std_fd)->stdin_fd = dup(STDIN_FILENO);
	(*std_fd)->stdout_fd = dup(STDOUT_FILENO);
	(*std_fd)->stderr_fd = dup(STDERR_FILENO);
	return (1);
}

void	refresh_std_fd(t_std_fd *std_fd)
{
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	dup2(std_fd->stdout_fd, STDOUT_FILENO);
	dup2(std_fd->stdin_fd, STDIN_FILENO);
	dup2(std_fd->stderr_fd, STDERR_FILENO);
}
