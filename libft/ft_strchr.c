/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:41:32 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/05 13:39:28 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// int main()
// {
//     const char string[] = "tripouille";
//     unsigned char find = 'z';

//     char *result = ft_strchr(string, 't'+ 256);
//     char *test = strchr(string, 't' + 256);
//     printf("eigen: %s", result);
// 	printf("echte: %s", test);
// 	if (result == NULL)
// 	{
// 		printf("NULL");
// 	}
// }