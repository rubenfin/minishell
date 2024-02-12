/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:40:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/12 13:40:09 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(t_env_ll *env, char *msg, int n)
{
	t_env_ll	*node;
	int			i;
	int			x;
	char		*key;

	node = NULL;
	i = 0;
	x = 0;
	if (ft_strchr(msg, '$'))
	{
		while (msg[i])
		{
			if (msg[i] == '$')
			{
				x = i + 1;
				while (msg[i] && msg[i] != ' ')
					i++;
				key = ft_strndup(msg + x, i - x);
				break ;
			}
			i++;
		}
	}
	i = 0;
	x = 0;
	while (msg[i])
	{
		if (msg[i] != '$')
			printf("%c", msg[i]);
		else if (msg[i] == '$' && msg[i + 1] && !ft_isalnum(msg[i + 1]))
			printf("%c", msg[i]);
		else
		{
			i += ft_strlen(key);
			node = find_key(env, key);
			if (node && node->value)
				printf("%s", node->value);
		}
		i++;
	}
	if (!n)
		printf("\n");
}

// int	main(void)
// {
//     echo("test", 1);
// 	return (0);
// }