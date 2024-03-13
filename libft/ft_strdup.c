/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:41:40 by jade-haa          #+#    #+#             */
/*   Updated: 2024/03/04 13:10:25 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	size;
	char	*emptyarray;

	i = 0;
	size = ft_strlen(s);
	emptyarray = malloc((size + 1) * sizeof(char));
	if (emptyarray == NULL)
		return (NULL);
	while (i < size)
	{
		emptyarray[i] = s[i];
		i++;
	}
	emptyarray[size] = '\0';
	return (emptyarray);
}

// int	main(void)
// {
// 	const char *orginal = (char *)"coucou";

// 	char *copy = ft_strdup(orginal);

// 	printf("%s", copy);

// 	free(copy);
// }