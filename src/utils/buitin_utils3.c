/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buitin_utils3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 17:00:22 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 17:00:48 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	equal_sign_check(t_env_ll **node, char **export_data, int *i, int j)
{
	if (!export_data[j][*i] || export_data[j][*i] != '=')
	{
		(*i)++;
		free(*node);
		return (0);
	}
	(*i)++;
	return (1);
}
