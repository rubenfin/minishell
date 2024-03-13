/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 10:42:45 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 15:35:19 by rfinneru      ########   odam.nl         */
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
	if (!expanded)
		return (NULL);
	return (expanded);
}

int	if_expanding_and_value(t_expanding **data, char **tmp)
{
	if (*tmp)
	{
		(*data)->expanded = ft_strjoin(*tmp, (*data)->value);
		if (!(*data)->expanded)
			return (ft_free(tmp), 0);
	}
	else
	{
		*tmp = ft_strjoin((*data)->expanded, (*data)->value);
		if (!*tmp)
			return (0);
		ft_free(&(*data)->expanded);
		ft_free(&(*data)->value);
		(*data)->expanded = ft_strdup(*tmp);
		ft_free(tmp);
		if (!(*data)->expanded)
			return (0);
		ft_free(&(*data)->until_dollar);
		return (1);
	}
	return (1);
}

char	*handle_expanding_str(t_expanding **data)
{
	char	*tmp;

	tmp = NULL;
	if (!(*data)->expanded)
		(*data)->expanded = expanded_doesnt_exist(&(*data)->until_dollar,
				&(*data)->value);
	else
	{
		if ((*data)->until_dollar)
		{
			tmp = ft_strjoin((*data)->expanded, (*data)->until_dollar);
			ft_free(&(*data)->expanded);
			(*data)->expanded = ft_strdup(tmp);
			ft_free(&tmp);
			ft_free(&(*data)->until_dollar);
		}
		if ((*data)->value)
		{
			if (!if_expanding_and_value(data, &tmp))
				return (ft_free(&tmp), free_expanding_data(data), NULL);
		}
	}
	ft_free2(&(*data)->value, &(*data)->until_dollar);
	ft_free(&tmp);
	return ((*data)->expanded);
}

int	from_and_until_dollar(t_expanding *data, char *result)
{
	if (result[data->i] != '$')
		data->until_dollar = find_until_dollar(result + data->i);
	else
		data->until_dollar = ft_strdup("");
	if (!data->until_dollar)
		return (free_expanding_data(&data), 0);
	data->from_dollar = ft_strnstr(&result[data->i], "$", ft_strlen(result));
	if (!data->from_dollar)
	{
		if (data->expanded)
		{
			data->tmp = ft_strjoin(data->expanded, data->until_dollar);
			if (!data->tmp)
				return (free_expanding_data(&data), 0);
			ft_free(&data->expanded);
			data->expanded = ft_strdup(data->tmp);
			ft_free(&data->tmp);
		}
		else
			data->expanded = ft_strdup(data->until_dollar);
		if (!data->expanded)
			return (free_expanding_data(&data), 0);
		return (ft_free(&data->until_dollar), 0);
	}
	return (1);
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
			return (free_expanding_data(&data), NULL);
		data->value = find_key_return_value_expanding(*env, data->tmp, status);
		if (!data->value)
			return (free_expanding_data(&data), NULL);
		ft_free(&data->tmp);
		data->expanded = handle_expanding_str(&data);
		if (!data->expanded)
			return (free_expanding_data(&data), NULL);
		ft_free(&data->value);
	}
	total = free_data_setup_return(data);
	return (total);
}
