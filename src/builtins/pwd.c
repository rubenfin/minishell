/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/11 11:00:03 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void pwd(t_env_ll *env)
{
	t_env_ll *node;
	node = find_key(env, "PWD=");
	printf("%s\n", node->value);
}

// int	main(void)
// {
// 	char *buffer;

// 	buffer = pwd();
// 	printf("%s", buffer);
// 	return (0);
// }