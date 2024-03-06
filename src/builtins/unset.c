/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:09 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 18:35:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(t_env_ll **env, char **unset_data)
{
	t_env_ll	*node;
	int			i;

	i = 0;
	while (unset_data[i])
	{
		node = find_key(*env, unset_data[i]);
		if (!node)
			return (EXIT_SUCCESS);
		if (!node->prev)
		{
			*env = node->next;
			node->next->prev = NULL;
		}
		else
		{
			node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
		}
		free(node->key);
		free(node->value);
		free(node);
		++i;
	}
	return (EXIT_SUCCESS);
}
