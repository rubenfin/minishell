/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:13:12 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/08 18:08:10 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_value_char(t_env_ll *env, char *value_str, int *i)
{
	t_env_ll	*value_ll;

	value_ll = env;
	if (!value_str || !value_str[0])
		return (NULL);
	while (value_ll)
	{
		if (!ft_strncmp(value_ll->key, value_str, ft_strlen(value_str) + 1))
		{
			*i += ft_strlen(value_str);
			return (ft_strdup(value_ll->value));
		}
		value_ll = value_ll->next;
	}
	return (NULL);
}
int	redirection_checker_int(char *str, int i, int check_all)
{
	if (check_all)
	{
		if (ft_strncmp(&str[i], "|", 1) == 0)
			return (5);
	}
	if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (RE_APPEND);
	if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (RE_HERE);
	if (ft_strncmp(&str[i], "<", 1) == 0)
		return (RE_IN);
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (RE_OUT);
	return (0);
}

int	redirection_checker_bool(char *str, int i, int check_all)
{
	if (check_all)
	{
		if (ft_strncmp(&str[i], "|", 1) == 0)
			return (1);
	}
	if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (1);
	if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (1);
	if (ft_strncmp(&str[i], "<", 1) == 0)
		return (1);
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (1);
	return (0);
}

int	check_first_cmd(char *str, int i)
{
	if (i == -1)
		return (1);
	while (str[i])
	{
		if (i == 0)
			return (1);
		if (str[i] == '|')
			return (1);
		if (str[i] != ' ')
			return (0);
		--i;
	}
	return (1);
}

int	dollar_sign_check(char *result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		if (ft_strncmp(&result[i], "$", 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	empty_checker(char *str)
{
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			break ;
		i++;
	}
	if (!str[i] || str[i] == ' ')
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '.' || str[i] == '/')
			flag = true;
		i++;
	}
	if (flag)
		return (1);
	write(STDERR_FILENO, "minishell: syntax error\n", 24);
	return (0);
}

char	*expanding(char *result, t_env_ll **env)
{
	int i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	int x;
	char *check;
	int j;

	x = 0;
	i = 0;
	j = 0;
	// if (result[0] == '$')
	// {
	// 	++i;
	// 	while (result[i])
	// 	{
	// 		if (!valid_identifier_check(result[i]))
	// 		{
	// 			i -= x;
	// 			break ;
	// 		}
	// 		i++;
	// 		x++;
	// 	}
	// 	if (!result[i])
	// 		i -= x;
	// 	check = ft_strndup(result + i, x);
	// 	tmp = find_value_char(*env, &check[0], &i);
	// 	if (!tmp)
	// 		return (ft_strdup(" "));
	// 	else
	// 		result = ft_strjoin(tmp, result + i);
	// 	return (result);
	// }
	while (result[i])
	{
		x = 0;
		if (result[i] == '$')
		{
			tmp = ft_substr(result, 0, i);
			i++;
			while (result[i])
			{
				if (!valid_identifier_check(result[i]))
				{
					i -= x;
					break ;
				}
				i++;
				x++;
			}
			if (!result[i])
				i -= x;
			check = ft_strndup(result + i, x);
			tmp2 = find_value_char(*env, &check[0], &i);
			if (!tmp2)
				tmp2 = ft_strdup("");
			if (tmp2)
			{
				tmp3 = ft_strjoin(tmp, tmp2);
				ft_free(&tmp);
				ft_free(&tmp2);
			}
			result = ft_strjoin(tmp3, result + (i));
		}
		j++;
		i++;
	}
	return (result);
}