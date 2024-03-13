/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:43:12 by jade-haa          #+#    #+#             */
/*   Updated: 2023/10/24 10:48:44 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkset(char const s1, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (s1 == set[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		size;
	char	*newarray;

	i = 0;
	len = ft_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	while (s1 && checkset(s1[i], set))
		i++;
	while (len > i && checkset(s1[len - 1], set))
		len--;
	size = len - i;
	newarray = (char *)malloc(sizeof(char) * (size + 1));
	if (newarray == NULL)
		return (NULL);
	ft_memcpy(newarray, &s1[i], size);
	newarray[size] = '\0';
	return (newarray);
}

// int main()
// {

//     char *newarray = ft_strtrim("ttloremr sit amet", "t");
//     printf("%s", newarray);
// 	free(newarray);
// }
