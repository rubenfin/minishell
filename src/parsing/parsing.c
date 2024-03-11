/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:55:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/11 14:31:43 by rfinneru      ########   odam.nl         */
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

int	set_node(t_command **param, char *str, int redirection, int len,
		t_env_ll **env, int status)
{
	char	*check;
	char	*result;

	if (len > 0)
	{
		check = ft_substr(str, 0, len);
		if (dollar_sign_check(check))
		{
			result = expanding(check, env, status);
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
		// printf("node aangemaakt normale : %s\n", result);
		ft_free(&check);
	}
	return (1);
}

char	*set_node_quotes(char *str, int quote, t_env_ll **env, int status)
{
	char	*check;
	char	*result;

	// printf("string voor expanden %s\n", str);
	if (dollar_sign_check(str) && quote == 34)
	{
		result = expanding(str, env, status);
		// printf("string na expanden : %s\n", result);
		return (result);
	}
	else
	{
		return (str);
	}
	ft_free(&check);
	return (NULL);
}

char	*quote_check(char *str, int *index, t_env_ll **env, int status)
{
	int		i;
	int		len;
	char	*result;
	char	quote;
	int		j;
	int		closing_quote;

	i = check_starting_quote(str);
	quote = str[i];
	closing_quote = check_closing_quote_with_quote(str, quote);
	// printf("starting = %c | closing_quote %c\n", str[i], str[closing_quote]);
	printf("index starting = %d | index closing %d\n", i, closing_quote);
	if (str[i] != str[closing_quote] || closing_quote == i)
	{
		syntax_error();
		return (NULL);
	}
	j = 0;
	len = 0;
	if (closing_quote == -1)
	{
		// printf("UNCLOSED QUOTES\n"); /////////////////////////heel lelijk ff opnieuw
		exit(1);
	}
	result = ft_substr_quotes(&str[1], i, closing_quote, quote);
	if (quote == '\"')
	{
		// printf("is double quote\n");
		result = set_node_quotes(result, quote, env, status);
	}
	*index = closing_quote + 1;
	return (result);
}

char	*get_cmd(char *str, int len, t_env_ll **env, int status)
{
	char	*origin;
	char	*result;
	char	*tmp;
	int		i;
	char	save;

	i = 0;
	origin = ft_substr(str, 0, len);
	result = ft_strdup("");
	while (origin[i])
	{
		if (origin[i] == '\'' || origin[i] == '\"')
		{
			save = origin[i];
			tmp = quote_check(&origin[i], &i, env, status);
			if (!tmp)
				return (NULL);
			result = ft_strjoin(result, tmp);
			i = check_closing_quote_with_quote(origin, save);
			ft_free(&tmp);
		}
		else
			result = ft_strjoin(result, ft_strndup(&origin[i], 1));
		++i;
	}
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
			// if (!check_if_closed(&str[i], quote))
			// {
			// 	printf("did not close : counter\n");
			// 	exit(EXIT_FAILURE);
			// }
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
	{
		return (quotes_len(str));
	}
	else
		return (no_quotes_len(str, redirection));
}

int	set_node_main(t_command **param, char *str, int redirection, t_env_ll **env,
		int status)
{
	char	*result;
	char	*builtin_check;
	int		len;

	len = get_size(str, redirection);
	builtin_check = ft_substr(str, 0, len);
	if (redirection == CMD && check_builtin(builtin_check))
		redirection = BUILTIN;
	if (redirection == CMD && total_quote(str) > 0)
	{
		result = get_cmd(str, len, env, status);
		if (!result)
			return (-1);
	}
	else
	{
		result = ft_substr(str, 0, len);
		result = expanding(result, env, status);
		// printf("zonder quotes gesubt%s\n", result);
	}
	if (createnode(param, result, redirection) == -1)
		return (-1);
	// printf("node gemaakt\n");
	return (len);
}

// int	get_quote_len(char *str)
// {
// 	int	len;
// 	int	quote;

// 	quote = str[0];
// 	len = 1;
// 	while (str[len])
// 	{
// 		if (str[len] == quote)
// 			break ;
// 		++len;
// 	}
// 	if (!str[len])
// 	{
// 		printf("exit quote_len\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (len);
// }

int	init_redirections(char *str, t_command **param, t_env_ll **env, int status)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;

	i = 0;
	command = *param;
	if (!empty_checker(str))
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
		}
		if (str && ft_strncmp(&str[i], "|", 1) == 0)
			redirection = PIPE;
		// printf("%d\n", len);
		len = set_node_main(param, &str[i], redirection, env, status);
		if (len == -1)
			return (0);
		if (len == -1)
			return (0);
		i += len;
	}
	return (1);
}
// int	get_quote_len(char *str)
// {
// 	int	len;
// 	int	quote;

// 	quote = str[0];
// 	len = 1;
// 	while (str[len])
// 	{
// 		if (str[len] == quote)
// 			break ;
// 		++len;
// 	}
// 	if (!str[len])
// 	{
// 		printf("exit quote_len\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (len);
// }
