/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 10:04:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/09 10:12:26 by rfinneru      ########   odam.nl         */
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