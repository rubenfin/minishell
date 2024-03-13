/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:41:48 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/05 13:39:38 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	convert(unsigned int index, char *c)
// {
// 	if (*c >= 'a' && *c <= 'z')
// 	{
// 		*c = *c - 'a' + 'A';
// 	}
// 	index++;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}

// int main()
// {
//     char string[] = "cap this";
//     ft_striteri(string, convert);
//     printf("%s", string);
// }