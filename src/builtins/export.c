/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/22 13:35:52 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_env_ll **env, char **export_data)
{
	t_env_ll *current;
	t_env_ll *node;
	int i;
	int j = 0;
	while (export_data[j])
	{
		i = 0;
		current = *env;
		node = (t_env_ll *)malloc(sizeof(t_env_ll));
		node->next = NULL;
		while (export_data[j][i])
		{
			if (export_data[j][i] == '=')
				break ;
			i++;
		}
		if (!export_data[j][i] || export_data[j][i] != '=')
			return ;
		i++;
		node->key = ft_strndup(export_data[j], i - 1);
		node->value = ft_strdup(export_data[j] + i);
		while (current->next)
			current = current->next;
		current->next = node;
		node->prev = current;
		++j;
	}
}