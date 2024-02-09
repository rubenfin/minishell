/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 12:35:32 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/09 13:13:28 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	make_env_ll(t_env_ll **env, char **envp)
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
			return ;
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		current->key = ft_strndup(envp[i], j + 1);
		if (!current->key)
			return ;
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
		}
		i++;
	}
	*env = head;
}
