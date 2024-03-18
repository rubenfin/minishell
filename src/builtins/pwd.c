/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:28:19 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/15 14:15:53 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_curr_dir(void)
{
	char	dir[PATH_MAX];
	char	*ret;

	ret = NULL;
	if (getcwd(dir, PATH_MAX))
		ret = ft_strdup(dir);
	if (!ret)
		return (NULL);
	return (ret);
}

int	pwd(t_env_ll *env)
{
	char	dir[PATH_MAX];

	(void)env;
	if (getcwd(dir, PATH_MAX))
	{
		write(STDOUT_FILENO, dir, ft_strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
		write(STDERR_FILENO,
			"minishell: error: failed to get current working directory\n", 58);
	return (1);
}
