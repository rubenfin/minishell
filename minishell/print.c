/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 12:44:23 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/02 12:45:23 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_arr(char **c)
{
	int i = 0;
	while (c[i])
	{
		printf("%s", c[i]);
		i++;
	}
}