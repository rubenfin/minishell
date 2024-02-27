/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/27 10:09:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 15:56:11 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	check_if_valid_exit(char *buffer)
// {
// 	int	i;
// 	int	total_spaces;

// 	total_spaces = 0;
// 	i = -1;
// 	while (buffer[++i] == ' ')
// 		;
// 	while (buffer[i++])
// 	{
// 		if (buffer[i] == )
// 	}
// 	return (print_exit_err(buffer, 1), EXIT_FAILURE);
// }

int	get_exit(t_env_ll *env, char **args, t_stream *iostream)
{
	(void)env;
	int exit_status;
	(void)exit_status;
	iostream->has_exit_been_called = true;
	if (!args[0])
		return (0);
	else
		return (ft_atoi(args[0]));
}