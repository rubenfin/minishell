/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 16:56:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/27 11:12:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_err(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(127);
}

void	print_file_dir_err(char *dir)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, dir, ft_strlen(dir));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
}

void	print_exit_err(char *buffer, bool numeric)
{
	if (numeric)
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
	else
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, buffer, ft_strlen(buffer));
		write(STDERR_FILENO, " :numeric argument required\n", 28);
	}
}