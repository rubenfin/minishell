/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 12:35:32 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/07 11:44:02 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strleng(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ll_to_2d_arr(t_env_ll *env)
{
	t_env_ll	*curr;
	char		**envp;
	int			i;
	char		*key_w_equal;

	i = 0;
	if (!env)
		return (NULL);
	curr = env;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	curr = env;
	envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = -1;
	while (curr)
	{
		key_w_equal = ft_strjoin(curr->key, "=");
		envp[++i] = ft_strjoin(key_w_equal, curr->value);
		ft_free(&key_w_equal);
		curr = curr->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*ft_strndup(char *s, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*temp;

	i = 0;
	while (s[i] && i < n)
		i++;
	temp = (char *)malloc((i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ptr = temp;
	i = 0;
	while (s[i] && i < n)
	{
		*ptr = s[i];
		ptr++;
		i++;
	}
	*ptr = '\0';
	return (temp);
}

int	make_env_ll(t_env_ll **env, char **envp)
{
	int			i;
	int			j;
	t_env_ll	*current;
	t_env_ll	*head;
	t_env_ll	*temp;

	i = 0;
	j = 0;
	*env = NULL;
	current = NULL;
	head = current;
	while (envp[i])
	{
		j = 0;
		current = (t_env_ll *)malloc(sizeof(t_env_ll));
		if (!current)
			return (-1);
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		current->key = ft_strndup(envp[i], j);
		if (!current->key)
			return (-1);
		if (envp[i][j] == '=')
			current->value = ft_strdup(envp[i] + j + 1);
		else
			current->value = NULL;
		current->next = NULL;
		if (!head)
			head = current;
		else
		{
			temp = head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = current;
			current->prev = temp;
		}
		i++;
	}
	*env = head;
	return(1);
}

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
	t_env_ll *value_ll = env;
	while (value_ll)
	{
		if (!ft_strncmp(value_ll->key, value_str, ft_strlen(value_str)))
			return (value_ll);
		value_ll = value_ll->next;
	}
	return (NULL);
}