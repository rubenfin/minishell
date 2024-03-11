/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 13:21:00 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/11 13:38:43 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_command_line(t_env_ll **env, t_command **command, char *arg, int status)
{
	*command = NULL;
	if (init_redirections(arg, command, env, status) == 0)
		return (0);
	return (1);
}

int	parser(t_env_ll **env, t_command **command, char *buffer, int status)
{
	if (!buffer || !buffer[0])
		return (ft_free(&buffer), 0);
	if (!init_command_line(env, command, buffer, status))
		return (ft_free(&buffer), 0);
	return (1);
}
