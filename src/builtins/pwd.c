/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 13:08:38 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_2d_arr(char **c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		printf("%s\n", c[i]);
		i++;
	}
}
char	*pwd(char **env)
{
	int	i;

	i = 0;
	while (!ft_strnstr(env[i], "PWD=", 4))
		i++;
	if (!env[i])
	{
		write(1, "here\n", 5);
		printf("nothing found in env from PWD");
		return (NULL);
	}
	else
		printf("%s\n", env[i] + 4);
	return (NULL);
}

// int	main(void)
// {
// 	char *buffer;

// 	buffer = pwd();
// 	printf("%s", buffer);
// 	return (0);
// }