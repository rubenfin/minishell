/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 15:58:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 15:58:30 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dollar_count(char *str)
{
	int	i;
	int	d_count;

	i = 0;
	d_count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			d_count++;
		i++;
	}
	return (d_count);
}

int	find_end_sign(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i])
	{
		if (!valid_identifier_check(str[i]) && str[i] != '?')
			return (i - 1);
		i++;
	}
	return (i);
}

char	*find_until_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	return (ft_strndup(str, i));
}