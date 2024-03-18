/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 09:51:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/15 14:48:14 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	change_pwd(t_env_ll **env, char *change_value)
{
	if (find_key_free_value(env, "OLDPWD"))
		get_key_change_value(env, "OLDPWD", find_key_return_value(*env, "PWD"));
	if (!get_key_change_value(env, "PWD", change_value))
		return (0);
	return (1);
}

int	find_key_free_value(t_env_ll **env, char *key_str)
{
	t_env_ll	*node;

	node = find_key(*env, key_str);
	if (!node)
		return (0);
	ft_free(&node->value);
	return (1);
}

char	*find_key_return_value(t_env_ll *env, char *key_str)
{
	t_env_ll	*key_ll;

	key_ll = env;
	while (key_ll)
	{
		if (!ft_strncmp(key_ll->key, key_str, max(ft_strlen(key_ll->key),
					ft_strlen(key_str))))
			return (key_ll->value);
		key_ll = key_ll->next;
	}
	return (NULL);
}

int	get_key_change_value(t_env_ll **env, char *key_str, char *change_value)
{
	t_env_ll	*node;

	node = find_key(*env, key_str);
	if (!node)
		return (0);
	if (change_value)
	{
		node->value = change_value;
	}
	return (1);
}
