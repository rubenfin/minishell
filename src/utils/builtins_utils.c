/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 09:51:12 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/26 11:28:47 by rfinneru      ########   odam.nl         */
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

void	change_pwd(t_env_ll **env, char *change_value)
{
	find_key_free_value(env, "OLDPWD");
	get_key_change_value(env, "OLDPWD", find_key_return_value(*env, "PWD"));
	get_key_change_value(env, "PWD", change_value);
}

void	find_key_free_value(t_env_ll **env, char *key_str)
{
	t_env_ll	*node;

	node = find_key(*env, key_str);
	ft_free(&node->value);
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

void	get_key_change_value(t_env_ll **env, char *key_str, char *change_value)
{
	t_env_ll	*node;

	node = find_key(*env, key_str);
	if (change_value)
	{
		node->value = change_value;
	}
}
