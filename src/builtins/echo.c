/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:40:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/08 10:48:13 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_for_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_env_ll *env, char **arg)
{
	int	i;

	i = 0;
	(void)env;
	if (!arg || !arg[0])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (!ft_strncmp(arg[0], "-n", 2) && !arg[1])
		return ;
	while (check_for_n(arg[i]))
		i++;
	while (arg[i])
	{
		write(STDOUT_FILENO, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		++i;
	}
	if (arg[0] && ft_strncmp(arg[0], "-n", 2))
		write(STDOUT_FILENO, "\n", 1);
}
