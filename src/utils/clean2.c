/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 11:42:50 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 16:59:40 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_all(t_cmd_data **data, t_stream *iostream, int total_pipes)
{
	if ((*data)->one_cmd)
		free_ll_command((*data)->one_cmd, false);
	if (*(*data)->command)
		free_ll_command(*(*data)->command, true);
	if (*data)
		free(*data);
	if (total_pipes)
		close_pipes(iostream->pipes);
	if (iostream->pipes)
		free(iostream->pipes);
	if (iostream)
		free(iostream);
}

void	ft_free2(char **string1, char **string2)
{
	ft_free(string1);
	ft_free(string2);
}
