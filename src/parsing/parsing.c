/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 15:55:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/08 16:01:36 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*createnode(t_command **head, char *data, int redirection)
{
	t_command	*newnode;
	t_command	*temp;

	newnode = (t_command *)malloc(sizeof(t_command));
	if (!newnode)
	{
		return (NULL);
	}
	newnode->string = data;
	newnode->token = redirection;
	newnode->next = NULL;
	if (*head == NULL)
	{
		*head = newnode;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newnode;
	}
	return (newnode);
}
int	directions_checker_int(char *str, int i, int check_all)
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

int	directions_checker_bool(char *str, int i, int check_all)
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
int	length_command(char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (0);
	while (command[i] && command[i] != ' ')
		i++;
	return (i + 1);
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

char	**get_path(char **envp)
{
	int		i;
	char	*path_string;
	char	**result_string;

	path_string = NULL;
	i = 0;
	while (!path_string)
	{
		path_string = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	result_string = ft_split(path_string, ':');
	if (!result_string)
		exit(1);
	return (result_string);
}

int	valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc(len * sizeof(char));
	if (!trimmed_command)
		return (0);
	ft_strlcpy(trimmed_command, argv, len);
	j = 0;
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (0);
		free(temp);
		if (access(str, X_OK) == 0)
			return (1);
		free(str);
		j++;
	}
	free(trimmed_command);
	return (0);
}

char	*set_valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc(len * sizeof(char));
	if (!trimmed_command)
		return (0);
	ft_strlcpy(trimmed_command, argv, len);
	j = 0;
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (NULL);
		free(temp);
		if (access(str, X_OK) == 0)
			break ;
		free(str);
		j++;
	}
	free(trimmed_command);
	return (str);
}

int	arg_counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*quote_check(char *str)
{
	int	x;
	int	i;

	i = 0;
	x = i + 1;
	++i;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			break ;
		++i;
	}
	return (ft_substr(str, x, i - x));
}

t_command	*init_redirections(char *str, t_command **param)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;
	char		*result;

	i = 0;
	command = *param;
	while (str[i])
	{
		redirection = CMD;
		len = 0;
		while (str[i] && (str[i] == ' ' || directions_checker_bool(&str[i], 0,
					0)))
		{
			if (directions_checker_bool(&str[i], 0, 0) && redirection == CMD)
				redirection = directions_checker_int(&str[i], 0, 0);
			++i;
		}
		if (ft_strncmp(&str[i], "|", 1) == 0)
			redirection = PIPE;
		while (str[i + len] && (str[i + len] != ' '))
		{
			++len;
			if (redirection == PIPE || directions_checker_bool(&str[i + len], 0,
					1))
				break ;
		}
		if (len > 0)
		{
			result = ft_substr(&str[i], 0, len);
			command = createnode(param, result, redirection);
		}
		i += len;
	}
	return (command);
}