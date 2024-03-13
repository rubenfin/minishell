/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:42:28 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/22 12:16:59 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	return (src_len);
}

// int main() {
//     char source[] = "This is a long string";
//     char destination[25];

//     size_t copied = ft_strlcpy(destination, source, 20);

//     printf("Copied: %zu\n", copied);
//     printf("Destination: %s\n", destination);

//     return (0);
// }

////////