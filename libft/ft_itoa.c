/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:38:43 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/22 11:52:36 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sizeint(int n, int *ptr)
{
	int	characters;
	int	size;

	size = 1;
	characters = 1;
	if (n < 0)
	{
		n *= -1;
		characters++;
	}
	while ((n / size) >= 10)
	{
		size *= 10;
		++characters;
	}
	*ptr = size;
	return (characters);
}

char	*putstring(char *result, int n, int size, int characters)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		result[0] = '-';
		i++;
	}
	while (i < characters)
	{
		result[i] = (n / size) + '0';
		n = n % size;
		size /= 10;
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		characters;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	characters = sizeint(n, &size);
	result = malloc(characters + 1);
	if (result == NULL)
		return (NULL);
	return (putstring(result, n, size, characters));
}

// int main()
// {
//     char *result = ft_itoa(1670);
//     printf("%s\n\n\n", result);
// 	free(result);
// }
