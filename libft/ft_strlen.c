/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/08 17:42:35 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/13 16:57:46 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i] != '\0')
		++i;
	return (i);
}

// int main()
// {
//     int n = strlen("oaisdfoi");
//     printf("%d", n);
// }
