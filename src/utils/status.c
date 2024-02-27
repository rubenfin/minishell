/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 10:02:57 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 11:05:18 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}

int set_file_failure_return(t_stream *iostream)
{
	iostream->file_failure = true;
	return(EXIT_FAILURE);
}

void	close_pipes(t_pipes *pipes)
{
	if (pipes->prev_read)
	{
		close(pipes->prev_write);
		close(pipes->prev_read);
	}
	if (pipes->curr_read)
	{
		close(pipes->curr_write);
		close(pipes->curr_read);
	}
}