/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/27 10:09:36 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/07 12:29:09 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	sign_count(char num)
{
	int	sign;

	sign = 1;
	if (num == '-')
	{
		sign = -1;
	}
	return (sign);
}

long long	ft_atoll(const char *nptr)
{
	long long	value;
	long long	sign;
	char		*num;
	long long	i;

	i = 0;
	value = 0;
	sign = 1;
	num = (char *)nptr;
	while (num[i] == ' ' || (num[i] >= 9 && num[i] <= 13))
	{
		i++;
	}
	if (num[i] == '-' || num[i] == '+')
	{
		sign = sign_count(num[i]);
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9')
	{
		value = value * 10 + (num[i] - '0');
		i++;
	}
	return (value * sign);
}

int	check_if_valid_exit(char **args)
{
	bool	found_not_numeric;
	int		i;
	int		j;
	int		total_min_or_plus;

	total_min_or_plus = 0;
	found_not_numeric = false;
	i = -1;
	j = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if ((!ft_isdigit(args[i][j]) && (args[i][j] != '-'
						&& args[i][j] != '+')))
				found_not_numeric = true;
			if (args[i][j] == '-' || args[i][j] == '+')
				total_min_or_plus++;
		}
	}
	if (i > 1)
		return (0);
	else if (found_not_numeric || total_min_or_plus > 1)
		return(0);
	return (1);
}

int	check_return(int i, bool found_not_numeric, char **args,
		int total_min_or_plus)
{
	if (i > 1)
		return (print_exit_err(args[0], false), 1);
	else if (found_not_numeric || total_min_or_plus > 1)
		return (print_exit_err(args[0], true), 2);
	if (!args[0])
		return (0);
	else
		return (ft_atoll(args[0]));
}

int	get_exit(t_env_ll *env, char **args)
{
	bool	found_not_numeric;
	int		i;
	int		j;
	int		total_min_or_plus;

	(void)env;
	total_min_or_plus = 0;
	found_not_numeric = false;
	i = -1;
	j = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if ((!ft_isdigit(args[i][j]) && (args[i][j] != '-'
						&& args[i][j] != '+')))
				found_not_numeric = true;
			if (args[i][j] == '-' || args[i][j] == '+')
				total_min_or_plus++;
		}
	}
	return (check_return(i, found_not_numeric, args, total_min_or_plus));
}
