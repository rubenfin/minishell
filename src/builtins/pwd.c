/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:28:19 by rfinneru          #+#    #+#             */
/*   Updated: 2024/02/13 12:06:25 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void pwd(t_env_ll *env)
{
	t_env_ll *node;
	node = find_key(env, "PWD=");
	write(1, node->value, ft_strlen(node->value));
}