/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing4.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 15:07:32 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/13 16:53:17 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initialize_variables(char **result, int *i)
{
	*result = NULL;
	*i = -1;
}

char	*get_cmd(char *str, int len, t_env_ll **env, int status)
{
	char	*origin;
	char	*result;
	char	*tmp;
	int		i;
	char	save;

	initialize_variables(&result, &i);
	origin = ft_substr(str, 0, len);
	if (!origin)
		return (NULL);
	while (origin[++i])
	{
		if (origin[i] == '\'' || origin[i] == '\"')
		{
			save = origin[i];
			tmp = quote_check(&origin[i], &i, env, status);
			if (!tmp)
				return (ft_free(&origin), ft_free(&result), NULL);
			i = check_closing_quote_with_quote(origin, save);
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
