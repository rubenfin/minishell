/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 14:44:10 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 15:32:30 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	(*data)->from_dollar = NULL;
	if ((*data))
		free((*data));
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

char	*free_data_setup_return(t_expanding *data)
{
	char	*return_value;

	return_value = ft_strdup(data->expanded);
	free_expanding_data(&data);
	if (!return_value)
		return (NULL);
	return (return_value);
}
