/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:40:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/11 20:34:25 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(t_env_ll *env, char *msg, int n)
{
	int			i;
	t_env_ll	*node;
	int			x;
	char		*key;

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
				if (!ft_strncmp(key, "", ft_strlen(key)));
					free(key);
				break ;
			}
			i++;
		}
	}
	i = 0;
	x = 0;
	
	while (msg[i])
	{
		if (msg[i] != '$' && !ft_isalnum(msg[i + 1]) && msg[i + 1])
			printf("%c", msg[i]);
		else
		{
			i++;
			while (msg[i] == key[x])
			{
				i++;
				x++;
			}
			node = find_key(env, key);
			if (node->value)
				printf("%s", node->value);
			continue;
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