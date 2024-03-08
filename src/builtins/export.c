/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/08 16:23:07 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	variable_exists(t_env_ll **node, t_env_ll **exist)
{
	ft_free(&(*exist)->key);
	ft_free(&(*exist)->value);
	(*exist)->key = ft_strdup((*node)->key);
	(*exist)->value = ft_strdup((*node)->value);
	free((*node)->key);
	free((*node)->value);
	free((*node));
	return (EXIT_SUCCESS);
}

int	check_if_valid(t_env_ll *node, char **export_data, int *i, int *j)
{
	while (export_data[*j][*i])
	{
		if (export_data[*j][*i] == '=')
		{
			if (export_data[*j][0] == '=')
				return (pr_invalid(&node, export_data, *j), 0);
			break ;
		}
		if (!valid_identifier_check(export_data[*j][*i]))
			return (pr_invalid(&node, export_data, *j), 0);
		(*i)++;
	}
	return (1);
}

int	equal_sign_check(t_env_ll *node, char **export_data, int *i, int j)
{
	if (!export_data[j][*i] || export_data[j][*i] != '=')
	{
		(*i)++;
		free(node);
		return (0);
	}
	(*i)++;
	return (1);
}

void	do_export(t_env_ll **env, char **export_data)
{
	t_env_ll	*node;
	t_env_ll	*exist;
	int			i;
	int			j;

	j = -1;
	while (export_data[++j])
	{
		i = 0;
		node = (t_env_ll *)malloc(sizeof(t_env_ll));
		node->next = NULL;
		if (!check_if_valid(node, export_data, &i, &j))
			return ;
		if (!equal_sign_check(node, export_data, &i, j))
			continue ;
		node->key = ft_strndup(export_data[j], i - 1);
		node->value = ft_strdup(export_data[j] + i);
		exist = find_key(*env, node->key);
		if (exist)
			variable_exists(&node, &exist);
		else
			put_node_at_end(env, &node);
	}
}

int	export(t_env_ll **env, char **export_data)
{
	if (!export_data || !export_data[0])
		return (print_export(*env), EXIT_SUCCESS);
	do_export(env, export_data);
	return (EXIT_SUCCESS);
}
