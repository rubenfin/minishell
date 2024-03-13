/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:42:56 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/22 12:33:16 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[j])
		{
			i++;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
		if (little[j] == '\0')
			return ((char *)&big[i - j]);
	}
	return (NULL);
}

// int main()
// {
//     const char big[] = "ausahfauahsohfo";
//     const char little[] = "a";

//     const char *result = strnstr(big, little, 20);

//     printf("%s", (const char *)result);

// }

// int main()
// {
//     const char big[] = "ausahfauahsohfo";
//     const char little[] = "x";

//     const char *result = ft_strnstr(big, little, 20);

//     if (result != NULL)
//     {
//         printf("%s", result);
//     }
//     else
//     {
//         printf("Substring not found\n");
//     }

//     return (0);
// }
