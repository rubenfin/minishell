/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:13:12 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/14 09:53:34 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_value_char(t_env_ll *env, char *value_str, int *i, int status)
{
	t_env_ll	*value_ll;

	value_ll = env;
	if (!value_str || !value_str[0])
		return (NULL);
	if (!ft_strncmp(value_str, "?", 1))
	{
		*i += 1;
		return (ft_strdup(ft_itoa(status)));
	}
	while (value_ll)
	{
		if (!ft_strncmp(value_ll->key, value_str, ft_strlen(value_str)))
		{
			*i += ft_strlen(value_str);
			return (ft_strdup(value_ll->value));
		}
		value_ll = value_ll->next;
	}
	*i += ft_strlen(value_str);
	return (NULL);
}

int	redirection_checker_int(char *str, int i, int check_all)
{
	if (check_all)
	{
		if (ft_strncmp(&str[i], "|", 1) == 0)
			return (5);
	}
	if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (RE_APPEND);
	if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (RE_HERE);
	if (ft_strncmp(&str[i], "<", 1) == 0)
		return (RE_IN);
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (RE_OUT);
	return (0);
}

int	check_first_cmd(char *str, int i)
{
	if (i == -1)
		return (1);
	while (str[i])
	{
		if (i == 0)
			return (1);
		if (str[i] == '|')
			return (1);
		if (str[i] != ' ')
			return (0);
		--i;
	}
	return (1);
}

int	dollar_sign_check(char *result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		if (ft_strncmp(&result[i], "$", 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	empty_checker(char *str)
{
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			break ;
		i++;
	}
	if (!str[i] || str[i] == ' ')
		return (0);
	i = -1;
	while (str[++i])
	{
		if (ft_isalnum(str[i]) || !valid_identifier_check(str[i]))
			flag = true;
	}
	if (flag)
		return (1);
	syntax_error();
	return (0);
}
