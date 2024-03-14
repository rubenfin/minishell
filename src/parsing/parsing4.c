/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing4.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 15:07:32 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/14 10:44:19 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*initialize_variables(char **result, int *i, char *str, int len)
{
	char	*origin;

	*result = NULL;
	*i = -1;
	origin = ft_substr(str, 0, len);
	if (!origin)
		return (NULL);
	return (origin);
}

char	*if_in_quotes(char *origin, int *i, t_env_ll **env, int status)
{
	char	save;
	char	*tmp;

	save = origin[*i];
	tmp = quote_check(&origin[*i], i, env, status);
	if (!tmp)
		return (ft_free(&origin), NULL);
	*i = check_closing_quote_with_quote(origin, save);
	return (tmp);
}

char	*get_cmd(char *str, int len, t_env_ll **env, int status)
{
	char	*origin;
	char	*result;
	char	*tmp;
	int		i;

	origin = initialize_variables(&result, &i, str, len);
	if (!origin)
		return (NULL);
	while (origin[++i])
	{
		if (origin[i] == '\'' || origin[i] == '\"')
		{
			tmp = if_in_quotes(origin, &i, env, status);
			if (!tmp)
				return (ft_free(&result), NULL);
			result = get_result(&result, &tmp);
		}
		else
			result = get_result_w_origin(&result, &origin[i]);
		if (!result)
			return (ft_free(&origin), NULL);
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
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && flag == 0)
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
