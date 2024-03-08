/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:44:02 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/08 16:44:38 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_ll	*find_key(t_env_ll *env, char *key_str)
{
	t_env_ll	*key_ll;

	key_ll = env;
	while (key_ll)
	{
		if (!ft_strncmp(key_ll->key, key_str, max(ft_strlen(key_ll->key),
					ft_strlen(key_str))))
			return (key_ll);
		key_ll = key_ll->next;
	}
	return (NULL);
}

t_env_ll	*find_value(t_env_ll *env, char *value_str)
{
	t_env_ll	*value_ll;

	value_ll = env;
	while (value_ll)
	{
		if (!ft_strncmp(value_ll->key, value_str, ft_strlen(value_str)))
			return (value_ll);
		value_ll = value_ll->next;
	}
	return (NULL);
}
