/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:42:50 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/05 13:39:55 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((s1[i] != s2[i]))
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int main() {
//     const char *str1 = "hello";
//     const char *str2 = "ahello";
//     int n = 6; // Number of characters to compare.

//     int result = ft_strncmp(str1, str2, n);

// 	printf("%d\n", result);
//     if (result == 0) {
//         printf("The first %d characters of str1 and str2 are identical.\n",
// n);
//     } else if (result < 0) {
//         printf("str1 is less than str2 in the first %d characters.\n", n);
//     } else {
//         printf("str1 is greater than str2 in the first %d characters.\n", n);
//     }

//     return (0);
// }