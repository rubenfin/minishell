/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 10:04:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/08 15:11:42 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_list(t_command *command)
{
	t_command	*print;

	print = command;
	while (print)
	{
		printf("command: %s\n", print->string);
		printf("Token : %d\n\n", print->token);
		print = print->next;
	}
}

void	print_2d_arrg(char **c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		printf("%s\n", c[i]);
		i++;
	}
}

void	print_env_ll(t_env_ll *env)
{
	while (env)
	{
		write(STDOUT_FILENO, env->key, ft_strlen(env->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, env->value, ft_strlen(env->value));
		write(STDOUT_FILENO, "\n", 1);
		env = env->next;
	}
}

void	print_export(t_env_ll *env)
{
	while (env)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, env->key, ft_strlen(env->key));
		write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, env->value, ft_strlen(env->value));
		write(STDOUT_FILENO, "\"\n", 2);
		env = env->next;
	}
}

void	pr_invalid(t_env_ll **node, char **export_data, int j)
{
	if (*node)
		free(*node);
	write(STDERR_FILENO, "minishell: export: ", 19);
	write(STDERR_FILENO, export_data[j], ft_strlen(export_data[j]));
	write(STDERR_FILENO, ": not a valid identifier\n", 25);
}
