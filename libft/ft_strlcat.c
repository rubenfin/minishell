/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:42:15 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/22 12:37:37 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	j = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	if (size == 0 || size <= dest_len)
		return (src_len + size);
	while (src[j] != '\0' && (dest_len + j) < (size - 1))
	{
		dest[dest_len + j] = src[j];
		j++;
	}
	dest[dest_len + j] = '\0';
	return (dest_len + src_len);
}

// int main(void) {
//     char *dest = (char *)malloc(15);
//     strcpy(dest, "hey");

//     const char *source = "World!";
//     size_t result = ft_strlcat(dest, "lorem ipsum dolor sit amet", 15);

//     printf("Concatenated: %s\n", dest);
//     printf("Result: %zu\n", result);

//     free(dest);
//     return (0);
// }