/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:39:01 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/01 14:09:12 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a1;
	const unsigned char	*a2;
	unsigned int		i;

	a1 = s1;
	a2 = s2;
	i = 0;
	while (i < n)
	{
		if (a1[i] != a2[i])
		{
			return (a1[i] - a2[i]);
		}
		i++;
	}
	return (0);
}

// int main()
// {
//    char s1[] = "a";
//    char s2[] = "a";
//    int n = 5;

//    int result = memcmp(s1, s2, n);

//    printf("%d", result);
// }