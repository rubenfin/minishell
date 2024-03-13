/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:41:01 by jade-haa          #+#    #+#             */
/*   Updated: 2023/11/05 13:39:17 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char a, int fd)
{
	write(fd, &a, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2147483648", 10);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar('-', fd);
			n = -n;
		}
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar(n % 10 + '0', fd);
		}
		if (n <= 9)
		{
			ft_putchar(n + '0', fd);
		}
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(-2147483648, 2);
// 	return (0);
// }