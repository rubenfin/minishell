/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_handling.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 12:56:47 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 10:27:29 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_std_fds(t_std_fd *std_fd)
{
	if (close(std_fd->stderr_fd) == -1)
		return (0);
	if (close(std_fd->stdin_fd) == -1)
		return (0);
	if (close(std_fd->stdout_fd) == -1)
		return (0);
	return (1);
}

int	refresh_std_fd(t_std_fd *std_fd)
{
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	if (dup2(std_fd->stdout_fd, STDOUT_FILENO) == -1)
		return (print_dup_err(), 0);
	if (dup2(std_fd->stdin_fd, STDIN_FILENO) == -1)
		return (print_dup_err(), 0);
	if (dup2(std_fd->stderr_fd, STDERR_FILENO) == -1)
		return (print_dup_err(), 0);
	return (1);
}
