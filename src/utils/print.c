/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:04:45 by rfinneru          #+#    #+#             */
/*   Updated: 2024/02/13 18:14:24 by jade-haa         ###   ########.fr       */
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

void		print_env_ll(t_env_ll *env)
{
	while (env)
	{
		// printf("%s%s\n", env->key, env->value);
		write(1, env->key, ft_strlen(env->key));
		
		write(1, env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
}
