/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:55:14 by rfinneru          #+#    #+#             */
/*   Updated: 2024/03/07 12:30:59 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:55:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 15:15:25 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_closing_quote(char *str, char quote)
{
	int	end;

	end = ft_strlen(str) - 1;
	while (str[end])
	{
		if (str[end] == quote)
			return (end);
		--end;
	}
	return (-1);
}

int	check_starting_quote(char *str)
{
	int	start;

	start = 0;
	while (str[start])
	{
		if (str[start] == 34 || str[start] == 27)
			return (start);
		++start;
	}
	return (-1);
}

int	quote_counter(const char *str, int quote)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == quote)
			++counter;
		++i;
	}
	return (counter);
}

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


// void	quotes_execeptions(char *str)
// {
// 	check_starting_quote(str)
// }
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
		printf("node aangemaakt normale : %s\n", result);
		ft_free(&check);
	}
	return (1);
}

int	set_node_quotes(t_command **param, char *str, int quote, int len,
		t_env_ll **env)
{
	char	*check;
	char	*result;

	if (len > 0)
	{
		check = ft_substr(str, 0, len);
		if (dollar_sign_check(check) && quote == 34)
		{
			result = expanding(check, env);
			ft_free(&check);
			if (createnode(param, result, 0) == -1)
				return (-1);
		}
		else
		{
			result = ft_substr(str, 0, len);
			if (createnode(param, result, 0) == -1)
				return (-1);
		}
		printf("node aangemaakt quotes : %s\n", result);
		ft_free(&check);
	}
	return (1);
}

int	quote_check(char *str)
{
	int		i;
	int		len;
	char	*result;
	char	quote;
	int		j;
	int		closing_quote;

	quote = str[0];
	i = 1;
	j = 0;
	len = 0;
	closing_quote = check_closing_quote(str, quote);
	if (closing_quote == -1)
		printf("UNCLOSED QUOTES\n");
	while (str && str[i])
	{
		if (str[i] && i == closing_quote)
		{
			printf("%d\n", i);
			result = ft_substr_quotes(&str[1], 0, i, quote);
			printf("result == %s\n", result);
			// if (set_node_quotes(param, result, quote, len, env) == -1)
			// 	return (-1);
			return (i + 1);
		}
		++len;
		++i;
	}
	return (0);
}

char *get_cmd(char *str, int len)
{
	char *origin;

	origin = ft_substr(str, 0, len);
	// quote_check(origin);
	return(origin);
}

int	set_node_main(t_command **param, char *str, int redirection, int len,
		t_env_ll **env)
{
	char *result;
	(void)param;
	(void)str;
	(void)len;
	(void)env;
	if (redirection == CMD)
		result = get_cmd(str, len);
	return(0);
}

int	init_redirections(char *str, t_command **param, t_env_ll **env)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;
	char		*test;
	i = 0;
	command = *param;
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
		if (set_node_main(param, &str[i], redirection, len, env) == -1)
			return (0);
		i += len;
		free(test);
	}
	return (1);
}
// if (str[i] == '\"' || str[i] == '\'')
// 			{
// 				temp = quote_check(param, &str[i], env);
// 				if (temp == -1)
// 					return (0);
// 				i += temp;
// 				temp = 0;
// 				break ;
// 			}