/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:09 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/09 12:24:14 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**unset(char **env, char *unset_data)
{
	char **new_unset_env;
	int i;
	int skip = -1;
	while (!ft_strnstr(env[++skip], unset_data, ft_strlen(unset_data)))
		;
	if (!env[skip])
		return (env);
	printf("%s\n", env[skip]);
	int j = -1;
	int x = 0;
	i = -1;
	while (env[++i])
		;
	new_unset_env = (char **)malloc(i * sizeof(char *));
	i = -1;
	while (env[++i])
	{
		if (i == skip)
			i++;
		j = 0;
		while (env[i][j])
			j++;
		new_unset_env[x] = (char *)malloc((j + 1) * sizeof(char));
		x++;
	}
	x = 0;
	j = -1;
	i = -1;
	while (env[++i])
	{
		if (i == skip)
			i++;
		j = 0;
		while (env[i][j])
		{
			new_unset_env[x][j] = env[i][j];
			j++;
		}
		new_unset_env[x][j] = '\0';
		x++;
	}
	new_unset_env[x] = 0;
	return (new_unset_env);
}