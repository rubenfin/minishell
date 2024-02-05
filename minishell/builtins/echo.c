/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 11:40:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/02 14:34:35 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static int	ft_strleng(char *string)

{
	int i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}
void	echo(char *msg, int n)
{
	int	i;

	i = 0;
	write(1, msg, ft_strleng(msg));
	if (!n)
		write(1, "\n", 1);
}

// int	main(void)
// {
//     echo("test", 1);
// 	return (0);
// }