/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:37:03 by jade-haa          #+#    #+#             */
/*   Updated: 2024/01/18 13:04:54 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	check_minus(char c)
// {
// 	if (c == '-')
// 	{
// 		return (-1);
// 	}
// 	return (1);
// }

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	sign;
// 	long long	result;

// 	i = 0;
// 	result = 0;
// 	sign = 1;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 	{
// 		i++;
// 	}
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		sign = check_minus(str[i]);
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		result = (result * 10) + (str[i] - '0');
// 		i++;
// 	}
// 	return (result * sign);
// }

#include <limits.h>

static int	check_minus(char c)
{
	if (c == '-')
	{
		return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		sign = check_minus(str[i]);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX / 10 || (result == INT_MAX / 10 && str[i]
				- '0' > INT_MAX % 10))
		{
			exit(EXIT_FAILURE);
		}
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (int)(result * sign);
}

// int main()
// {
//     char string[] = "-234235";

//     int result = ft_atoi(string);
//     printf("%d", result);
// }