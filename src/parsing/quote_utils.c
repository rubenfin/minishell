/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/11 13:54:58 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 09:31:23 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_closing_quote_with_quote(char *str, char quote)
{
	int	end;

	end = ft_strlen(str) - 1;
	while (str[end])
	{
		if (str[end] == quote)
			return (end);
		--end;
	}
	return (-1);
}

int	check_closing_quote(char *str)
{
	int	end;

	end = ft_strlen(str) - 1;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"')
			return (end);
		--end;
	}
	return (-1);
}

int	check_starting_quote(char *str)
{
	int	start;

	start = 0;
	while (str[start])
	{
		if (str[start] == '\'' || str[start] == '\"')
			return (start);
		++start;
	}
	return (-1);
}

int	quote_counter(const char *str, int quote)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == quote)
			++counter;
		++i;
	}
	return (counter);
}

int	total_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		++i;
	}
	return (0);
}
