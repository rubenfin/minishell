/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:55:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/05 16:35:18 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

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

char	*expanding(char *result, t_env_ll **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		x;
	char	*check;
	int		j;

	x = 0;
	i = 0;
	j = 0;
	if (result[0] == '$')
	{
		++i;
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
		tmp = find_value_char(*env, &check[0], &i);
		if (!tmp)
			return (ft_strdup(""));
		else
			result = ft_strjoin(tmp, result + i);
		return (result);
	}
	while (result[i])
	{
		if (result[i] == '$')
		{
			tmp = ft_substr(result, 0, i);
			printf("%s\n", tmp);
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
				return (tmp);
			if (tmp2)
			{
				tmp3 = ft_strjoin(tmp, tmp2);
				ft_free(&tmp);
				ft_free(&tmp2);
			}
			result = ft_strjoin(tmp3, result + (i));
			return (result);
		}
		j++;
		i++;
	}
	return (NULL);
}
int	set_node(t_command **param, char *str, int redirection, int len,
		t_env_ll **env)
{
	char	*check;
	char	*result;

	if (len > 0)
	{
		check = ft_substr(str, 0, len);
		if (dollar_sign_check(check))
		{
			result = expanding(check, env);
			ft_free(&check);
			redirection = CMD;
			if (createnode(param, result, redirection) == -1)
				return (-1);
		}
		else
		{
			result = ft_substr(str, 0, len);
			if (createnode(param, result, redirection) == -1)
				return (-1);
		}
		ft_free(&check);
	}
	return (1);
}
int	quote_check(t_command **param, char *str, t_env_ll **env,
		t_stream *iostream)
{
	int		i;
	int		len;
	char	*result;
	char	qoute;
	int		j;

	(void)iostream;
	qoute = str[0];
	i = 1;
	j = 0;
	len = 0;
	while (str && str[i])
	{
		if (str[i] && str[i] == qoute)
		{
			result = ft_substr(&str[1], 0, len);
			if (set_node(param, result, 0, len, env) == -1)
				return (-1);
			return (i + 1);
		}
		++len;
		++i;
	}
	return (0);
}

int	empty_check(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	init_redirections(char *str, t_command **param, t_env_ll **env,
		t_stream *iostream)
{
	int i;
	t_command *command;
	int len;
	int redirection;
	char *test;
	int temp;

	// char *result;
	i = 0;
	command = *param;
	if (!empty_check(str))
		return (0);
	while (str[i])
	{
		redirection = CMD;
		len = 0;
		while (str[i] && (str[i] == ' ' || redirection_checker_bool(&str[i], 0,
					0)))
		{
			if (redirection_checker_bool(&str[i], 0, 0) && redirection == CMD)
				redirection = redirection_checker_int(&str[i], 0, 0);
			++i;
			if (str[i] == '\"' || str[i] == '\'')
			{
				temp = quote_check(param, &str[i], env, iostream);
				if (temp == -1)
					return (0);
				i += temp;
				temp = 0;
				break ;
			}
		}
		if (str && ft_strncmp(&str[i], "|", 1) == 0)
			redirection = PIPE;
		while (str && str[i + len] && (str[i + len] != ' '))
		{
			++len;
			if (redirection == PIPE || redirection_checker_bool(&str[i + len],
					0, 1))
				break ;
		}
		test = ft_substr(&str[i], 0, len);
		if (redirection == CMD && check_first_cmd(str, i - 1)
			&& check_builtin(test))
			redirection = BUILTIN;
		if (set_node(param, &str[i], redirection, len, env) == -1)
			return (0);

		i += len;
		free(test);
	}
	return (1);
}