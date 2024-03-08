/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 12:40:47 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/08 12:42:19 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_lost_parent_err(void)
{
	write(STDERR_FILENO, "minishell: cd: error retrieving current directory:",
		51);
	write(STDERR_FILENO,
		"getcwd: cannot access parent directories: No such file or directory\n",
		68);
}
