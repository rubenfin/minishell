/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:38:53 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/05 13:38:40 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int		i;
	const unsigned char	*us;

	us = s;
	i = 0;
	while (i < n)
	{
		if (us[i] == (unsigned char)c)
		{
			return ((char *)&us[i]);
		}
		i++;
	}
	return (NULL);
}

// int main() {
//     unsigned char memory_block[] = {0x10, 0x20, 0x30, 0x40, 0x50};
//     int search_value = 0x30;
//     size_t search_size = 5;

//     void *result = memchr(memory_block, search_value, search_size);

//     if (result != NULL) {
//         size_t i = (unsigned char *)result - memory_block;
//         printf("Byte 0x%02X found at position %zu.\n", search_value, i);
//     } else {
//         printf("Byte 0x%02X not found in the memory block.\n", search_value);
//     }

//     return (0);
// }