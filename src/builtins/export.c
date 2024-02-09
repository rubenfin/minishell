/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 11:26:11 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/09 18:51:03 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**export(char **env, char *export_data)
{
	char	**copied_env;
	int		i;
	int		length;
	int		j;

	length = 0;
	while (env[length])
		length++;
	copied_env = (char **)malloc((length + 2) * sizeof(char *));
	i = -1;
	j = 0;
	while (env[++i])
	{
		j = 0;
		while (env[i][j])
			j++;
		copied_env[i] = (char *)malloc((j + 1) * sizeof(char));
	}
	copied_env[i] = (char *)malloc((ft_strlen(export_data) + 1) * sizeof(char));
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j])
		{
			copied_env[i][j] = env[i][j];
			j++;
		}
		copied_env[i][j] = '\0';
	}
	j = 0;
	while (export_data[j])
	{
		copied_env[i][j] = export_data[j];
		j++;
	}
	copied_env[i][j] = '\0';
	i++;
	copied_env[i] = 0;
	return (copied_env);
}
