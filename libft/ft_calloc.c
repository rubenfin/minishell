/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:37:34 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/22 12:42:38 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (nmemb == 0 || size == 0)
	{
		return (malloc(1));
	}
	if (nmemb > SIZE_MAX / size)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, nmemb * size);
	}
	return (ptr);
}

// int main() {
//     size_t nmemb = 4;
//     size_t size = sizeof(char);

//     char *result = (char *)ft_calloc(nmemb, size);

//     if (result == NULL) {
//         return (1); }

//     for (size_t i = 0; i < nmemb * size; i++) {
//         printf("%d ", result[i]);
//     }
//     printf("\n");

//     free(result);

//     return (0);
// }
