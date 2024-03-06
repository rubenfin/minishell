/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 13:21:00 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 14:19:18 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_command_line(t_env_ll **env, t_command **command, char *arg)
{

	*command = NULL;
	if (init_redirections(arg, command, env) == 0)
		return (0);
	return (1);
}

int	parser(t_env_ll **env, t_command **command, char *buffer)
{
	if (!buffer || !buffer[0])
		return (0);
	init_command_line(env, command, buffer);
	return (1);
}
