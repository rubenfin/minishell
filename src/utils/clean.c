/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 18:56:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/17 10:25:51 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free(char **buffer)
{
	if (*buffer)
		free(*buffer);
	buffer = NULL;
}

void	free_ll(t_env_ll *env)
{
	while (env->next)
	{
		env = env->next;
		free(env->prev->key);
		free(env->prev->value);
		free(env->prev);
	}
	free(env->key);
	free(env->value);
	free(env);
}

