/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing3.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 15:05:10 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/13 16:47:57 by rfinneru      ########   odam.nl         */
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

char	*set_node_quotes(char **str, int quote, t_env_ll **env, int status)
{
	char	*result;

	if (dollar_sign_check(*str) && quote == 34)
	{
		result = expanding(*str, env, status);
		if (!result)
			return (ft_free(str), NULL);
		ft_free(str);
		return (result);
	}
	else
	{
		result = ft_strdup(*str);
		if (!result)
			return (ft_free(str), NULL);
		ft_free(str);
		return (result);
	}
}

char	*quote_check(char *str, int *index, t_env_ll **env, int status)
{
	int		i;
	char	*result;
	char	*saved;
	char	quote;
	int		closing_quote;

	result = NULL;
	i = check_starting_quote(str);
	quote = str[i];
	closing_quote = check_closing_quote_with_quote(str, quote);
	if (str[i] != str[closing_quote] || closing_quote == i)
		return (syntax_error(), NULL);
	saved = ft_substr_quotes(&str[1], i, closing_quote, quote);
	if (quote == '\"')
		result = set_node_quotes(&saved, quote, env, status);
	*index = closing_quote + 1;
	return (result);
}

char	*get_result(char **result, char **tmp)
{
	char	*returned_result;

	if (*result)
		returned_result = ft_strjoin(*result, *tmp);
	else
		returned_result = ft_strdup(*tmp);
	if (!returned_result)
		return (ft_free2(result, tmp), NULL);
	ft_free(result);
	ft_free(tmp);
	return (returned_result);
}
