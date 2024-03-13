/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 17:00:43 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	variable_exists(t_env_ll **node, t_env_ll **exist)
{
	ft_free(&(*exist)->key);
	ft_free(&(*exist)->value);
	(*exist)->key = ft_strdup((*node)->key);
	if (!(*exist)->key)
		return (0);
	(*exist)->value = ft_strdup((*node)->value);
	if (!(*exist)->value)
		return (ft_free(&(*exist)->key), 0);
	free((*node)->key);
	free((*node)->value);
	free((*node));
	return (1);
}

int	create_nodes(t_env_ll *node, char **export_data, int i, int j)
{
	node->key = ft_strndup(export_data[j], i - 1);
	if (!node->key)
		return (free(node), 0);
	node->value = ft_strdup(export_data[j] + i);
	if (!node->value)
		return (ft_free(&node->key), free(node), 0);
	return (1);
}

int	set_node_right_place(t_env_ll **env, t_env_ll *node)
{
	t_env_ll	*exist;

	exist = find_key(*env, node->key);
	if (exist)
	{
		if (!variable_exists(&node, &exist))
			return (ft_free(&node->key), ft_free(&node->value), free(node), 0);
	}
	else
		put_node_at_end(env, &node);
	return (1);
}

int	do_export(t_env_ll **env, char **export_data)
{
	t_env_ll	*node;
	int			i;
	int			j;

	j = -1;
	while (export_data[++j])
	{
		i = 0;
		node = (t_env_ll *)malloc(sizeof(t_env_ll));
		if (!node)
			return (0);
		node->next = NULL;
		if (!check_if_valid(node, export_data, &i, &j))
			return (0);
		if (!equal_sign_check(&node, export_data, &i, j))
			continue ;
		if (!create_nodes(node, export_data, i, j))
			return (0);
		if (!set_node_right_place(env, node))
			return (0);
	}
	return (1);
}

int	export(t_env_ll **env, char **export_data)
{
	if (!export_data || !export_data[0])
		return (print_export(*env), EXIT_SUCCESS);
	if (!do_export(env, export_data))
		return (-1);
	return (EXIT_SUCCESS);
}
