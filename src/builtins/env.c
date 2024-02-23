/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 13:18:28 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/23 13:58:40 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_env(t_env_ll **env, char **args)
{
	if (args[0])
		export(env, args);
	print_env_ll(*env);
}

// int	main(int ac, char **av, char **env)
// {
// 	get_env(env);
// 	return (0);
// }