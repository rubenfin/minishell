/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 10:42:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 11:04:23 by rfinneru      ########   odam.nl         */
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
char	*find_key_return_value_expanding(t_env_ll *env, char *key_str,
		int status)
{
	t_env_ll	*key_ll;

	key_ll = env;
	if (!key_str[0])
		return ("$");
	if (!ft_strncmp(key_str, "?", 1))
		return (ft_itoa(status));
	while (key_ll)
	{
		if (!ft_strncmp(key_ll->key, key_str, max(ft_strlen(key_ll->key),
					ft_strlen(key_str))))
			return (key_ll->value);
		key_ll = key_ll->next;
	}
	return (NULL);
}

char	*handle_expanding_str(char *expanded, char **until_dollar, char *value)
{
	char	*tmp;

	// char	*tmp2;
	if (!expanded)
	{
		if (value)
			expanded = ft_strjoin(*until_dollar, value);
		else
			expanded = ft_strdup(*until_dollar);
	}
	else
	{
		tmp = ft_strjoin(expanded, *until_dollar);
		ft_free(&expanded);
		if (value)
			expanded = ft_strjoin(tmp, value);
		else
			expanded = ft_strdup(tmp);
		ft_free(&tmp);
	}
	ft_free(until_dollar);
	return (expanded);
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
			until_dollar = ft_strdup("");
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
		// printf("ud: %s\n beyfore fd: %s\n", until_dollar, from_dollar);
		end = find_end_sign(from_dollar);
		tmp = ft_strndup(from_dollar + 1, end);
		i += ft_strlen(tmp);
		// printf("fd after: %s\n", tmp);
		value = find_key_return_value_expanding(*env, tmp, status);
		ft_free(&tmp);
		expanded = handle_expanding_str(expanded, &until_dollar, value);
	}
	return (expanded);
}
