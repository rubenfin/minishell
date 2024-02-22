/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 16:56:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/22 16:58:11 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_cmd_err(char *cmd)
{
    	printf("%s: command not found\n", cmd);
		exit(127);
}