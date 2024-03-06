/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:40:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 18:34:58 by rfinneru      ########   odam.nl         */
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
	int	x;
	int	j;

	i = 0;
	x = 0;
	j = 0;
	(void)env;
	if (!arg || !arg[0])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	while (check_for_n(arg[j]))
		j++;
	while (arg[j])
	{
		write(STDOUT_FILENO, arg[j], ft_strlen(arg[j]));
		if (arg[j + 1])
			write(1, " ", 1);
		++j;
	}
	if (arg[0] && ft_strncmp(arg[0], "-n", 2))
		write(STDOUT_FILENO, "\n", 1);
}
