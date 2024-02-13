/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:26:09 by rfinneru          #+#    #+#             */
/*   Updated: 2024/02/13 12:06:13 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_env_ll *env, char **unset_data)
{
	t_env_ll *node;
	int i = 0;
	while (unset_data[i])
	{
		node = find_key(env, unset_data[i]);
		if (!node)
			return ;
		node->prev->next = node->next;
		free(node->key);
		free(node->value);
		free(node);
		++i;
	}
}