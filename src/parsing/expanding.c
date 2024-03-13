/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 10:42:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 12:56:23 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expanded_doesnt_exist(char **until_dollar, char **value)
{
	char	*expanded;

	expanded = NULL;
	if (*value)
	{
		if (*until_dollar)
			expanded = ft_strjoin(*until_dollar, *value);
		else
			expanded = ft_strdup(*value);
	}
	else
	{
		if (*until_dollar)
			expanded = ft_strdup(*until_dollar);
	}
	ft_free(value);
	ft_free(until_dollar);
	return (expanded);
}
char	*handle_expanding_str(char **expanded, char **until_dollar,
		char **value)
{
	char	*tmp;

	tmp = NULL;
	if (!*expanded)
		*expanded = expanded_doesnt_exist(until_dollar, value);
	else
	{
		if (*until_dollar)
		{
			tmp = ft_strjoin(*expanded, *until_dollar);
			ft_free(expanded);
			*expanded = ft_strdup(tmp);
			ft_free(&tmp);
			ft_free(until_dollar);
		}
		if (*value)
		{
			if (tmp)
				*expanded = ft_strjoin(tmp, *value);
			else
			{
				tmp = ft_strjoin(*expanded, *value);
				ft_free(expanded);
				ft_free(value);
				ft_free(until_dollar);
				return (tmp);
			}
			ft_free(&tmp);
			ft_free(value);
			ft_free(until_dollar);
		}
	}
	ft_free(value);
	ft_free(until_dollar);
	ft_free(&tmp);
	return (*expanded);
}

int	init_expanding(t_expanding **data)
{
	(*data) = (t_expanding *)malloc(sizeof(t_expanding));
	if (!(*data))
		return (0);
	(*data)->i = 0;
	(*data)->expanded = NULL;
	(*data)->end = 0;
	(*data)->from_dollar = NULL;
	(*data)->until_dollar = NULL;
	(*data)->tmp = NULL;
	(*data)->value = NULL;
	return (1);
}

int	from_and_until_dollar(t_expanding *data, char *result)
{
	if (result[data->i] != '$')
		data->until_dollar = find_until_dollar(result + data->i);
	else
		data->until_dollar = NULL;
	data->from_dollar = ft_strnstr(&result[data->i], "$", ft_strlen(result));
	if (!data->from_dollar)
	{
		if (data->expanded)
		{
			data->tmp = ft_strjoin(data->expanded, data->until_dollar);
			ft_free(&data->expanded);
			data->expanded = ft_strdup(data->tmp);
			ft_free(&data->tmp);
		}
		else
			data->expanded = ft_strdup(data->until_dollar);
		ft_free(&data->until_dollar);
		return (0);
	}
	return (1);
}

int	end_of_expanding_char(t_expanding *data)
{
	data->i += ft_strlen(data->until_dollar) + 1;
	data->end = find_end_sign(data->from_dollar);
	data->tmp = ft_strndup(data->from_dollar + 1, data->end);
	if (!data->tmp)
		return (0);
	data->i += ft_strlen(data->tmp);
	return (1);
}

void	free_expanding_data(t_expanding **data)
{
	if ((*data)->value)
		ft_free(&(*data)->value);
	if ((*data)->expanded)
		ft_free(&(*data)->expanded);
	if ((*data)->until_dollar)
		ft_free(&(*data)->until_dollar);
	if ((*data)->tmp)
		ft_free(&(*data)->tmp);
	(*data)->i = 0;
	(*data)->end = 0;
	if ((*data))
		free((*data));
}

char	*free_data_setup_return(t_expanding *data)
{
	char	*return_value;

	return_value = ft_strdup(data->expanded);
	// ft_free(&data->expanded);
	// free(data);
	free_expanding_data(&data);
	if (!return_value)
		return (NULL);
	return (return_value);
}

char	*expanding(char *result, t_env_ll **env, int status)
{
	t_expanding	*data;
	char		*total;

	data = NULL;
	if (!init_expanding(&data))
		return (NULL);
	while (result[data->i])
	{
		if (!from_and_until_dollar(data, result))
			break ;
		if (!end_of_expanding_char(data))
			return (NULL);
		data->value = find_key_return_value_expanding(*env, data->tmp, status);
		if (!data->value)
			return (NULL);
		ft_free(&data->tmp);
		data->expanded = handle_expanding_str(&data->expanded,
				&data->until_dollar, &data->value);
		if (!data->expanded)
			return (NULL);
		ft_free(&data->value);
	}
	total = free_data_setup_return(data);
	return (total);
}
