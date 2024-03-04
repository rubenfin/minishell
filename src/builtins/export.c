/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/04 11:18:35 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_env_ll **env, char **export_data)
{
	t_env_ll *current;
	t_env_ll *node;
	int i;
	int j = 0;
	if (!export_data)
		return(1);
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
		{
			free(node);
			j++;
			continue ;
		};
		i++;
		node->key = ft_strndup(export_data[j], i - 1);
		node->value = ft_strdup(export_data[j] + i);
		while (current->next)
			current = current->next;
		current->next = node;
		node->prev = current;
		++j;
	}
	return (EXIT_SUCCESS);
}