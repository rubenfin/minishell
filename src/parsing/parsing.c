/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 13:51:40 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 10:24:28 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_size(char *str, int redirection)
{
	if (total_quote(str) > 0)
		return (quotes_len(str));
	else
		return (no_quotes_len(str, redirection));
}

int	get_len_and_check_builtin(int *len, int *redirection, char *str)
{
	char	*temp;

	*len = get_size(str, *redirection);
	temp = ft_substr(str, 0, *len);
	if (!temp)
		return (0);
	if (*redirection == CMD && check_builtin(temp))
		*redirection = BUILTIN;
	ft_free(&temp);
	return (1);
}

char	*set_node_main(char *str, int *redirection, t_env_ll **env, int status)
{
	char	*result;
	int		len;
	char	*temp;

	if (!get_len_and_check_builtin(&len, redirection, str))
		return (NULL);
	if (*redirection == CMD && total_quote(str) > 0)
	{
		result = get_cmd(str, len, env, status);
		if (!result)
			return (NULL);
	}
	else
	{
		temp = ft_substr(str, 0, len);
		if (!temp)
			return (NULL);
		result = expanding(temp, env, status);
		if (!result)
			return (ft_free(&temp), NULL);
		ft_free(&temp);
	}
	return (result);
}

int	determine_redirection(char *str, int *i, int *redirection)
{
	while (str[*i] && (str[*i] == ' ' || redirection_checker_bool(&str[*i], 0,
				0)))
	{
		if (redirection_checker_bool(&str[*i], 0, 0) && *redirection == CMD)
			*redirection = redirection_checker_int(&str[*i], 0, 0);
		++(*i);
	}
	if (str && ft_strncmp(&str[*i], "|", 1) == 0)
		*redirection = PIPE;
	return (*redirection);
}

int	init_redirections(char *str, t_command **param, t_env_ll **env, int status)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;
	char		*result;

	i = 0;
	command = *param;
	if (!empty_checker(str))
		return (0);
	while (str[i])
	{
		redirection = CMD;
		determine_redirection(str, &i, &redirection);
		len = get_size(&str[i], redirection);
		result = set_node_main(&str[i], &redirection, env, status);
		if (!result)
			return (0);
		if (createnode(param, result, redirection) == -1)
			return (0);
		if (len == -1)
			return (0);
		i += len;
	}
	return (1);
}
