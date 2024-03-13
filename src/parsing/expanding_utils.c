/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 15:58:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 15:32:56 by rfinneru      ########   odam.nl         */
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
	char	*status_str;
	char	*status_and_text;

	if (!key_str[0])
		return (ft_strdup("$"));
	if (!ft_strncmp(key_str, "?", 1))
	{
		status_str = ft_itoa(status);
		if (key_str + 1)
		{
			status_and_text = ft_strjoin(status_str, key_str + 1);
			ft_free(&status_str);
			return (status_and_text);
		}
		return (status_str);
	}
	while (env)
	{
		if (!ft_strncmp(env->key, key_str, max(ft_strlen(env->key),
					ft_strlen(key_str))))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
