/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/05 16:26:31 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_identifier_check(char c)
{
	if ((c > 122 && c < 127) || (c > 90 && c < 95) || (c < 65 && c > 58)
		|| (c < 65 && c > 58) || (c < 48))
		return (0);
	else
		return (1);
}

int	export(t_env_ll **env, char **export_data)
{
	t_env_ll	*current;
	t_env_ll	*node;
	t_env_ll	*exist;
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (!export_data || !export_data[0])
		return (print_export(*env), EXIT_SUCCESS);
	while (export_data[j])
	{
		i = 0;
		current = *env;
		node = (t_env_ll *)malloc(sizeof(t_env_ll));
		node->next = NULL;
		while (export_data[j][i])
		{
			if (export_data[j][i] == '=')
			{
				if (export_data[j][0] == '=')
					return (print_invalid_identifier(&node, export_data, j),
						EXIT_FAILURE);
				break ;
			}
			if (!valid_identifier_check(export_data[j][i]))
				return (print_invalid_identifier(&node, export_data, j),
					EXIT_FAILURE);
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
		exist = find_key(*env, node->key);
		if (exist)
		{
			ft_free(&exist->key);
			ft_free(&exist->value);
			exist->key = ft_strdup(node->key);
			exist->value = ft_strdup(node->value);
			free(node->key);
			free(node->value);
			free(node);
			return (EXIT_SUCCESS);
		}
		while (current->next)
			current = current->next;
		current->next = node;
		node->prev = current;
		++j;
	}
	return (EXIT_SUCCESS);
}
