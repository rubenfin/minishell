/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 10:42:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 17:38:27 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expanded_doesnt_exist(char **until_dollar, char **value)
{
	char	*expanded;

	expanded = NULL;
	if (*value)
	{
		if (*until_dollar)
			expanded = ft_strjoin(*until_dollar, *value);
		else
			expanded = ft_strdup(*value);
		ft_free(value);
	}
	else
	{
		if (*until_dollar)
			expanded = ft_strdup(*until_dollar);
	}
	return (expanded);
}
char	*handle_expanding_str(char **expanded, char **until_dollar,
		char **value)
{
	char	*tmp;

	tmp = NULL;
	if (!*expanded)
		*expanded = expanded_doesnt_exist(until_dollar, value);
	else
	{
		if (*until_dollar)
		{
			tmp = ft_strjoin(*expanded, *until_dollar);
			ft_free(expanded);
			*expanded = ft_strdup(tmp);
			ft_free(&tmp);
		}
		if (*value)
		{
			if (tmp)
			{
				*expanded = ft_strjoin(tmp, *value);
			}
			else
			{
				tmp = ft_strjoin(*expanded, *value);
				ft_free(expanded);
				ft_free(value);
				return (tmp);
			}
			ft_free(&tmp);
			ft_free(value);
		}
	}
	ft_free(until_dollar);
	ft_free(&tmp);
	return (*expanded);
}

char	*expanding(char *result, t_env_ll **env, int status)
{
	int		i;
	int		end;
	char	*tmp;
	char	*value;
	char	*expanded;
	char	*until_dollar;
	char	*from_dollar;

	(void)status;
	i = 0;
	expanded = NULL;
	while (result[i])
	{
		if (result[i] != '$')
			until_dollar = find_until_dollar(result + i);
		else
			until_dollar = NULL;
		from_dollar = ft_strnstr(&result[i], "$", ft_strlen(result));
		if (!from_dollar)
		{
			if (expanded)
			{
				tmp = ft_strjoin(expanded, until_dollar);
				ft_free(&expanded);
				expanded = ft_strdup(tmp);
				ft_free(&tmp);
			}
			else
				expanded = ft_strdup(until_dollar);
			ft_free(&until_dollar);
			break ;
		}
		i += ft_strlen(until_dollar) + 1;
		end = find_end_sign(from_dollar);
		tmp = ft_strndup(from_dollar + 1, end);
		i += ft_strlen(tmp);
		value = find_key_return_value_expanding(*env, tmp, status);
		ft_free(&tmp);
		expanded = handle_expanding_str(&expanded, &until_dollar, &value);
	}
	return (expanded);
}
