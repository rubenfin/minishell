/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/11 11:53:24 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_env_ll *env, char *export_data)
{
	t_env_ll *current;
	t_env_ll *node;
	current = env;
	node = (t_env_ll *)malloc(sizeof(t_env_ll));
	node->next = NULL;
	int i = 0;
	while(export_data[i])
	{
		if (export_data[i] == '=')
			break;
		i++;
	}
	if (!export_data[i] || export_data[i] != '=')
		return;
	i++;
	node->key = ft_strndup(export_data, i);
	node->value = ft_strdup(export_data + i);
	while (current->next)
		current = current->next;
	current->next = node;
	node->prev = current;
}