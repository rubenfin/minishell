/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/27 10:09:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 16:33:33 by rfinneru      ########   odam.nl         */
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

	bool found_not_numeric;
	found_not_numeric = false;
	int i = -1;
	int j = -1;
	while (args[++i])
	{
		j = 0;
		while (args[i][++j])
		{
			if (!ft_isdigit(args[i][j]))
				found_not_numeric = true;
		}
	}
	if (i > 1)
	{
		print_exit_err(args[0], false);
		return (1);
	}
	else if (found_not_numeric)
	{
		print_exit_err(args[0], true);
        return(2);
	}
	iostream->has_exit_been_called = true;
	if (!args[0])
		return (0);
	else
		return (ft_atoi(args[0]));
}