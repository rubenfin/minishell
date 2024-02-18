/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 18:56:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/18 09:55:45 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
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

void	free_ll_command(t_command *head, bool free_first_pipe,
		bool main_command)
{
	t_command	*save;
	t_command	*curr;

	curr = head;
	if (!free_first_pipe)
	{
		if (curr->token == PIPE)
			curr = curr->next;
	}
	while (curr)
	{
		save = curr->next;
		if (main_command)
			free(curr->string);
		free(curr);
		curr = save;
	}
}
