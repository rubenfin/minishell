/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_own_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 15:23:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/02 15:23:56 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**malloc_my_own_env(char **env, char **making_my_own_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	making_my_own_env = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++;
		making_my_own_env[i] = (char *)malloc((j + 1) * sizeof(char));
		i++;
	}
	return (making_my_own_env);
}

char	**make_my_env(char **env)
{
	char	**making_my_own_env;
	int		i;
	int		j;

	making_my_own_env = NULL;
	i = 0;
	j = 0;
	making_my_own_env = malloc_my_own_env(env, making_my_own_env);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			making_my_own_env[i][j] = env[i][j];
			j++;
		}
		making_my_own_env[i][j] = '\0';
		i++;
	}
	making_my_own_env[i] = 0;
	return (making_my_own_env);
}