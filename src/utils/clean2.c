/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 11:42:50 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/07 11:46:23 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all_close_pipes(t_cmd_data **data, t_stream *iostream,
		int total_pipes)
{
	free_ll_command((*data)->one_cmd, false);
	free_ll_command(*(*data)->command, true);
	free(*data);
	if (total_pipes)
		close_pipes(iostream->pipes);
	free(iostream->pipes);
	free(iostream);
}
