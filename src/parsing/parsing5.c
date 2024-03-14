/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing5.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 10:23:42 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 10:44:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*get_result_w_origin(char **result, char *origin)
{
	char	*origin_tmp;
	char	*returned_result;

	origin_tmp = ft_strndup(origin, 1);
	if (*result)
		returned_result = ft_strjoin(*result, origin_tmp);
	else
		returned_result = ft_strdup(origin_tmp);
	if (!returned_result)
		return (ft_free2(result, &origin_tmp), NULL);
	ft_free(result);
	ft_free(&origin_tmp);
	return (returned_result);
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
