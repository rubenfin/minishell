/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 13:18:28 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/11 10:55:50 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void get_env(t_env_ll *env)
{
	print_env_ll(env);
}

// int	main(int ac, char **av, char **env)
// {
// 	get_env(env);
// 	return (0);
// }