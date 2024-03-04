/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:55:14 by rfinneru          #+#    #+#             */
/*   Updated: 2024/03/04 11:59:38 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_value_char(t_env_ll *env, char *value_str)
{
	t_env_ll *value_ll = env;
	while (value_ll)
	{
			// printf("%s\n", value_ll->value);
		if (!ft_strncmp(value_ll->key, value_str, ft_strlen(value_str)))
		{
			return (value_ll->value);
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
char	*find_flag(char *command)
{
	int		i;
	int		j;
	char	*flag;

	i = 0;
	if (!command[i])
		return (NULL);
	j = i;
	while (command[j])
		j++;
	flag = malloc(j * sizeof(char) + 1);
	if (!flag)
		return (NULL);
	j = 0;
	while (command[i])
		flag[j++] = command[i++];
	flag[j] = '\0';
	return (flag);
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
	int	i;

	i = 0;
	if (ft_strncmp(&result[0], "$", 1) == 0)
	{
		++i;
		result = find_value_char(*env, &result[i]);
		return (ft_strdup(result));
	}
	while (result[i])
	{
		if (ft_strncmp(&result[i], "$", 1) == 0)
			return (ft_substr(result, 0, i));
		i++;
	}
	return (NULL);
}
void	set_node(t_command **param, char *str, int redirection, int len,
		t_env_ll **env)
{
	char	*result;

	if (len > 0)
	{
		result = ft_substr(str, 0, len);
		// printf("%s\n", result);
		if (dollar_sign_check(result))
		{
			// printf("dollar_sign\n");
			result = expanding(result, env);
			redirection = CMD;
			createnode(param, result, redirection);
		}
		else
		{
			// printf("normale\n");
			result = ft_substr(str, 0, len);
			createnode(param, result, redirection);
		}
		// printf("end result == %s\n\n\n", result);
	}
}
int	quote_check(t_command **param, char *str, t_env_ll **env)
{
	int		i;
	int		len;
	char	qoute;

	qoute = str[0];
	i = 1;
	len = 0;
	while (str && str[i])
	{
		if (str[i] && str[i] == qoute)
		{
			set_node(param, &str[1], 0, len, env);
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

int	init_redirections(char *str, t_command **param, t_env_ll **env)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;
	char		*test;

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
				i += quote_check(param, &str[i], env);
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
		set_node(param, &str[i], redirection, len, env);
		i += len;
		free(test);
	}
	return (1);
}