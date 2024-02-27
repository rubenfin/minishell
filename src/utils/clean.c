/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 18:56:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 09:34:13 by rfinneru      ########   odam.nl         */
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
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_iostream(t_stream **iostream, int count)
{
	int	i;

	i = 0;
	i = -1;
	while (++i < count)
		free((*iostream)->args[i]);
	free((*iostream)->args);
	free((*iostream)->pipes);
	free((*iostream));
}

void	free_all_close_pipes(t_command *saved, t_command *until_pipe,
		t_stream *iostream, int total_pipes)
{
	free_ll_command(until_pipe, false);
	free_ll_command(saved, true);
	if (total_pipes)
		close_pipes(iostream->pipes);
	free(iostream->pipes);
	free(iostream);
}