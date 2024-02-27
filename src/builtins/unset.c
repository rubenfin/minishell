/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:09 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 13:56:12 by rfinneru      ########   odam.nl         */
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

// 0x12 -> shell -> zsh
// 0x16 -> pwd -> dir
// null

// minishell
// {
// 	t_env_ll* env;
// 	unset(&env);
// 				{
// 					env = 0x12;
// 					*env => shell;
// 					copy van location of shell;
// 					free(env->value);
// 					free(env);
// 					env = null;
// 					env -> 0x0;
// 				}
// 	env -> 0x12;
// }