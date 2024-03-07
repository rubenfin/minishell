/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing_utils3.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 13:55:08 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/07 13:55:24 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(char *arg)
{
	if (ft_strncmp(arg, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(arg, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(arg, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(arg, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(arg, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(arg, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(arg, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

int	get_builtin(char *command, t_stream *param, t_env_ll **env)
{
	char	**args;

	args = param->args;
	if (ft_strncmp(command, "echo", 5) == 0)
		return (echo(*env, args), 0);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (cd(env, args));
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (pwd(*env));
	else if (ft_strncmp(command, "export", 7) == 0)
		return (export(env, args));
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (unset(env, args));
	else if (ft_strncmp(command, "env", 4) == 0)
		return (get_env(env, args));
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (get_exit(*env, args));
	else
		return (127);
}
