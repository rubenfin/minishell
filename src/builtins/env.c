/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 13:18:28 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 14:05:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_env(t_env_ll **env, char **args)
{
	(void)args;
	print_env_ll(*env);
	return(EXIT_SUCCESS);
}

// int	main(int ac, char **av, char **env)
// {
// 	get_env(env);
// 	return (0);
// }