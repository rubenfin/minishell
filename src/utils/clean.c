/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 18:56:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/25 11:37:04 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

void	free_ll(t_env_ll **env)
{
	while ((*env)->next)
	{
		(*env) = (*env)->next;
		free((*env)->prev->key);
		free((*env)->prev->value);
		free((*env)->prev);
	}
	free((*env)->key);
	free((*env)->value);
	free((*env));
}

void	free_ll_command(t_command *head, bool main_command)
{
	t_command	*save;
	t_command	*curr;

	curr = head;
	while (curr)
	{
		save = curr->next;
		if (main_command)
			free(curr->string);
		free(curr);
		curr = save;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}