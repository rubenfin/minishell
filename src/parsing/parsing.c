/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 13:51:40 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 13:59:41 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fill_substr(char const *s, int start, int len, int quote)
{
	int		i;
	char	*substring;
	int		quote_amount;

	start = 0;
	quote_amount = quote_counter(s, quote);
	substring = (char *)malloc((len + 1 - quote_amount) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (i < len - quote_amount && s[start])
	{
		if (s[start] == quote)
			++start;
		substring[i] = s[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
char	*ft_substr_quotes(char const *s, unsigned int start, size_t len,
		char quote)
{
	char	*substring;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size || len == 0)
		return (errorarray());
	if (len > size - start)
		len = size - start;
	substring = fill_substr(s, start, len, quote);
	return (substring);
}
char	*set_node_quotes(char *str, int quote, t_env_ll **env, int status)
{
	char	*check;
	char	*result;

	if (dollar_sign_check(str) && quote == 34)
	{
		result = expanding(str, env, status);
		return (result);
	}
	else
		return (str);
	ft_free(&check);
	return (NULL);
}
char	*quote_check(char *str, int *index, t_env_ll **env, int status)
{
	int		i;
	int		len;
	char	*result;
	char	quote;
	int		closing_quote;

	i = check_starting_quote(str);
	quote = str[i];
	closing_quote = check_closing_quote_with_quote(str, quote);
	if (str[i] != str[closing_quote] || closing_quote == i)
	{
		syntax_error();
		return (NULL);
	}
	len = 0;
	result = ft_substr_quotes(&str[1], i, closing_quote, quote);
	if (quote == '\"')
		result = set_node_quotes(result, quote, env, status);
	*index = closing_quote + 1;
	return (result);
}

char	*get_result(char **result, char **tmp)
{
	char	*returned_result;

	if (*result)
	{
		returned_result = ft_strjoin(*result, *tmp);
	}
	else
		returned_result = ft_strdup(*tmp);
	ft_free(result);
	ft_free(tmp);
	return (returned_result);
}

char	*get_result_w_origin(char **result, char *origin)
{
	char	*origin_tmp;
	char	*returned_result;

	origin_tmp = ft_strndup(origin, 1);
	if (*result)
	{
		returned_result = ft_strjoin(*result, origin_tmp);
	}
	else
		returned_result = ft_strdup(origin_tmp);
	ft_free(result);
	ft_free(&origin_tmp);
	return (returned_result);
}

char	*get_cmd(char *str, int len, t_env_ll **env, int status)
{
	char	*origin;
	char	*result;
	char	*tmp;
	int		i;
	char	save;

	result = NULL;
	i = 0;
	origin = ft_substr(str, 0, len);
	if (!origin)
		return (NULL);
	while (origin[i])
	{
		if (origin[i] == '\'' || origin[i] == '\"')
		{
			save = origin[i];
			tmp = quote_check(&origin[i], &i, env, status);
			if (!tmp)
				return (ft_free(&origin), NULL);
			i = check_closing_quote_with_quote(origin, save);
			result = get_result(&result, &tmp);
		}
		else
			result = get_result_w_origin(&result, &origin[i]);
		if (!result)
			return (ft_free(&origin), NULL);
		++i;
	}
	ft_free(&origin);
	return (result);
}

int	no_quotes_len(char *str, int redirection)
{
	int	len;

	len = 0;
	while (str && str[len] && (str[len] != ' '))
	{
		++len;
		if (redirection == PIPE || redirection_checker_bool(&str[len], 0, 1))
			break ;
	}
	return (len);
}
int	quotes_len(char *str)
{
	int	i;
	int	flag;
	int	quote;

	quote = -1;
	i = 0;
	flag = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if ((str[i] == 27 || str[i] == 34) && flag == 0)
		{
			flag = 1;
			quote = str[i];
			i++;
		}
		else if ((str[i] == quote || str[i] == quote) && flag)
		{
			flag = 0;
			quote = 0;
		}
		if (str[i] == ' ' && !flag)
			break ;
		++i;
	}
	return (i);
}
int	get_size(char *str, int redirection)
{
	if (total_quote(str) > 0)
		return (quotes_len(str));
	else
		return (no_quotes_len(str, redirection));
}
char	*set_node_main(char *str, int *redirection, t_env_ll **env, int status)
{
	char	*result;
	char	*temp;
	int		len;

	len = get_size(str, *redirection);
	temp = ft_substr(str, 0, len);
	if (!temp)
		return (NULL);
	if (*redirection == CMD && check_builtin(temp))
		*redirection = BUILTIN;
	ft_free(&temp);
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
			return(NULL);
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
	while (str && str[i])
	{
		redirection = CMD;
		determine_redirection(str, &i, &redirection);
		len = get_size(&str[i], redirection);
		result = set_node_main(&str[i], &redirection, env, status);
		if (!result)
			return (free_ll_command(*param, true), 0);
		if (createnode(param, result, redirection) == -1)
			return (free_ll_command(*param, true), 0);
		if (len == -1)
			return (free_ll_command(*param, true), 0);
		i += len;
	}
	return (1);
}
