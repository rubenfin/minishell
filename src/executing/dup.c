/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 11:00:18 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/15 11:01:09 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dup_single(t_stream *iostream)
{
	if (iostream->input != -1)
	{
		if (dup2(iostream->input, STDIN_FILENO) == -1)
			exit(errno);
	}
	if (iostream->output != -1)
	{
		if (dup2(iostream->output, STDOUT_FILENO) == -1)
			exit(errno);
	}
}

void	ft_dup_pipes(t_stream *iostream)
{
	if (iostream->input != -1)
	{
		if (dup2(iostream->input, STDIN_FILENO) == -1)
			exit(errno);
	}
	if (iostream->input != iostream->pipes->curr_read)
		close(iostream->pipes->curr_read);
	if (iostream->output != -1)
	{
		if (dup2(iostream->output, STDOUT_FILENO) == -1)
			exit(errno);
	}
	if (iostream->output != iostream->pipes->curr_write)
		close(iostream->pipes->curr_write);
}
