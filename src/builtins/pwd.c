/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/26 14:22:41 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_env_ll *env)
{
	(void)env;
	char dir[PATH_MAX];
	if (getcwd(dir, PATH_MAX))
	{
		write(STDOUT_FILENO, dir, ft_strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
		write(STDERR_FILENO, "ERROR\n", 6);
	return (1);
}