/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:42:44 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/22 12:18:28 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	convert_to_upper(unsigned int i, char c)
// {
// 	if (c >= 'a' && c <= 'z')
// 	{
// 		return (c - 'a' + 'A');
// 	}
// 	return (c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*result;

	len = ft_strlen(s);
	i = 0;
	if (s == NULL)
		return (NULL);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}

// int	main(void)
// {
// 	const char input[] = "Hello, World!";
// 	char *output = ft_strmapi(input, convert_to_upper);

// 	if (output != NULL)
// 	{
// 		printf("Modified String: %s\n", output);
// 		free(output);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}

// 	return (0);
// }