/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:40:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/11 11:08:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(char *msg, int n)
{
	write(1, msg, ft_strlen(msg));
	if (!n)
		write(1, "\n", 1);
}

// int	main(void)
// {
//     echo("test", 1);
// 	return (0);
// }