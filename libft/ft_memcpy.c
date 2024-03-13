/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:39:09 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/05 13:38:53 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*p;
	const char		*a;

	a = src;
	p = dest;
	i = 0;
	if (p == NULL && a == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		p[i] = a[i];
		i++;
	}
	return (dest);
}

// int main() {
//     char source[] = "Hello, World!";
//     char destination[20];
//     char destination1[] = "h";

//     memcpy(destination1, source, strlen(source) + 1);

//     printf("Destination: %s\n", destination);

//     return (0);
// }