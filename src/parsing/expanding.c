/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 10:42:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 15:58:28 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_key_return_value_expanding(t_env_ll *env, char *key_str,
		int status)
{
	t_env_ll	*key_ll;
	char		*status_str;
	char		*status_and_text;

	key_ll = env;
	if (!key_str[0])
		return ("$");
	if (!ft_strncmp(key_str, "?", 1))
	{
		status_str = ft_itoa(status);
		if (key_str[1])
		{
			status_and_text = ft_strjoin(status_str, key_str + 1);
			ft_free(&status_str);
			return (status_and_text);
		}
		return (status_str);
	}
	while (key_ll)
	{
		if (!ft_strncmp(key_ll->key, key_str, max(ft_strlen(key_ll->key),
					ft_strlen(key_str))))
			return (ft_strdup(key_ll->value));
		key_ll = key_ll->next;
	}
	return (NULL);
}

char	*handle_expanding_str(char *expanded, char **until_dollar, char **value)
{
	char	*tmp;

	if (!expanded)
	{
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
	}
	else
	{
		tmp = ft_strjoin(expanded, *until_dollar);
		ft_free(&expanded);
		if (*value)
		{
			expanded = ft_strjoin(tmp, *value);
			ft_free(value);
		}
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
		expanded = handle_expanding_str(expanded, &until_dollar, &value);
	}
	return (expanded);
}
