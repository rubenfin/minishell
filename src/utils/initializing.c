/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initializing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 16:17:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 16:17:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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