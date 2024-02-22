/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:55:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/22 14:33:44 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirection_checker_int(char *str, int i, int check_all)
{
	if (check_all)
	{
		if (ft_strncmp(&str[i], "|", 1) == 0)
			return (5);
	}
	if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (RE_APPEND);
	if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (RE_HERE);
	if (ft_strncmp(&str[i], "<", 1) == 0)
		return (RE_IN);
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (RE_OUT);
	return (0);
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
char	*find_flag(char *command)
{
	int		i;
	int		j;
	char	*flag;

	i = 0;
	if (!command[i])
		return (NULL);
	j = i;
	while (command[j])
		j++;
	flag = malloc(j * sizeof(char) + 1);
	if (!flag)
		return (NULL);
	j = 0;
	while (command[i])
		flag[j++] = command[i++];
	flag[j] = '\0';
	return (flag);
}

int	check_first_cmd(char *str, int i)
{
	if (i == -1)
		return(1);
	while (str[i])
	{
		if (i == 0)
			return (1);
		if (str[i] == '|')
			return (1);
		if (str[i] != ' ')
			return (0);
		--i;
	}
	return (1);
}
void	set_node(t_command **param, char *str, int redirection, int len)
{
	char		*result;

	if (len > 0)
	{
		result = ft_substr(str, 0, len);
		// if (redirection == CMD && check_first_cmd(&str[0], len)
		// 	&& check_builtin(result))
		// 	printf("valid builtin!! == %c\n", str[0]);
		createnode(param, result, redirection);
	}
}
int	quote_check(t_command **param, char *str)
{
	int		i;
	int		len;
	char	qoute;

	qoute = str[0];
	i = 1;
	len = 0;
	while (str[i])
	{
		if (str[i] == qoute)
		{
			set_node(param, &str[1], 0, len);
			return (i + 1);
		}
		++len;
		++i;
	}
	exit(EXIT_FAILURE);
	return (0);
}

t_command	*init_redirections(char *str, t_command **param)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;

	// char *result;
	i = 0;
	command = *param;
	while (str[i])
	{
		redirection = CMD;
		len = 0;
		while (str[i] && (str[i] == ' ' || redirection_checker_bool(&str[i], 0,
					0)))
		{
			// printf("werkt");
			if (redirection_checker_bool(&str[i], 0, 0) && redirection == CMD)
				redirection = redirection_checker_int(&str[i], 0, 0);
			++i;
			if (str[i] == '\"' || str[i] == '\'')
			{
				// printf("%c\n", str[i]);
				i += quote_check(param, &str[i]);
				break ;
			}
		}
		if (ft_strncmp(&str[i], "|", 1) == 0)
			redirection = PIPE;
		while (str[i + len] && (str[i + len] != ' '))
		{
			++len;
			if (redirection == PIPE || redirection_checker_bool(&str[i + len],
					0, 1))
				break ;
		}
		char *test = ft_substr(&str[i], 0, len);
		if (redirection == CMD && check_first_cmd(str, i - 1) && check_builtin(test))
			redirection = BUILTIN;
		set_node(param, &str[i], redirection, len);
		i += len;
		free(test);
	}
	return (command);
}
