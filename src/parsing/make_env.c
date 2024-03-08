/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 12:35:32 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/08 16:48:41 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_ll_len(t_env_ll *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
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
	i = count_ll_len(env);
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
	envp[++i] = NULL;
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

int	initalize_node(t_env_ll *current, char **envp, int i, int j)
{
	current->key = ft_strndup(envp[i], j);
	if (!current->key)
		return (-1);
	if (envp[i][j] == '=')
		current->value = ft_strdup(envp[i] + j + 1);
	else
		current->value = NULL;
	current->next = NULL;
	return (0);
}

int	make_env_ll(t_env_ll **env, char **envp)
{
	int			i;
	int			j;
	t_env_ll	*current;
	t_env_ll	*head;

	i = -1;
	j = 0;
	current = NULL;
	head = NULL;
	while (envp[++i])
	{
		j = 0;
		current = (t_env_ll *)malloc(sizeof(t_env_ll));
		if (!current)
			return (-1);
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		initalize_node(current, envp, i, j);
		if (!head)
			head = current;
		else
			put_node_at_end(&head, &current);
	}
	*env = head;
	return (1);
}
