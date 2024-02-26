/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 16:56:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/26 11:26:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_err(char *cmd)
{
	printf("%s: command not found\n", cmd);
	exit(127);
}

void	print_file_dir_err(char *dir)
{
	write(1, "cd: ", 4);
	write(1, dir, ft_strlen(dir));
	write(1, ": No such file or directory\n", 28);
}