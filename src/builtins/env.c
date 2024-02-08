/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 13:18:28 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 13:09:15 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_env(char **env)
{
	char	*env_one_string;
	int		i;
	int		j;
	int		x;
	int		length;

	i = 0;
	j = 0;
	x = 0;
	length = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			j++;
			length++;
		}
		length++;
		i++;
	}
	i = 0;
	j = 0;
	env_one_string = malloc(length + 1 * sizeof(char));
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			env_one_string[x] = env[i][j];
            x++;
			j++;
		}
		env_one_string[x] = '\n';
		x++;
        i++;
	}
	env_one_string[x] = '\0';
	printf("%s", env_one_string);
}

// int	main(int ac, char **av, char **env)
// {
// 	get_env(env);
// 	return (0);
// }