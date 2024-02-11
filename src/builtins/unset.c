/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:09 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/11 12:02:51 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_env_ll *env, char *unset_data)
{
	t_env_ll *node;

	node = find_key(env, unset_data);
	if (!node)
		return;
	node->prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}