/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 16:36:54 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/02/25 11:04:18 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_command **param)
{
	int			count;
	t_command	*command;

	count = 0;
	command = *param;
	while (command && command->token != PIPE)
	{
		if (command->token == CMD)
			count++;
		command = command->next;
	}
	return (count);
}

void	set_args(t_command **param, t_stream *iostream, int count)
{
	int			i;
	t_command	*command;

	i = 0;
	command = *param;
	if (command->token == PIPE || command->token == BUILTIN)
		command = command->next;
	while (i < count)
	{
		if (command->token == CMD)
			iostream->args[i++] = ft_strdup(command->string);
		command = command->next;
	}
	iostream->args[i] = NULL;
}

int	check_builtin(char *arg)
{
	if (ft_strncmp(arg, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(arg, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(arg, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(arg, "export", 7) == 0)
		return (1);
	if (ft_strncmp(arg, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(arg, "env", 4) == 0)
		return (1);
	return (0);
}

int	get_builtin(char *command, t_stream *param, t_env_ll **env)
{
	char	**args;

	// char	*command;
	args = param->args;
	if (ft_strncmp(command, "echo", 5) == 0)
	{
		echo(*env, args);
		return (1);
	}
	if (ft_strncmp(command, "cd", 3) == 0)
	{
		cd(env, args[0]);
		return (1);
	}
	if (ft_strncmp(command, "pwd", 4) == 0)
	{
		pwd(*env);
		return (1);
	}
	if (ft_strncmp(command, "export", 7) == 0)
	{
		export(env, args);
		// print_env_ll(env);
		return (1);
	}
	if (ft_strncmp(command, "unset", 6) == 0)
	{
		// printf("Werkt");
		unset(env, args);
		return (1);
	}
	if (ft_strncmp(command, "env", 4) == 0)
	{
		get_env(env, args);
		return (1);
	}
	return (0);
}

void	execute_single(t_command **param, t_stream *iostream)
{
	t_command	*command;
	int			count;
	char		**env_from_ll;
	char		**paths;
	char		*cmd;
	// int			i;

	command = *param;
	if (command->token == PIPE)
		command = command->next;
	count = count_commands(&command);
	iostream->args = (char **)malloc(sizeof(char *) * (count + 1));
	set_args(param, iostream, count);
	if (iostream->input != -1)
		dup2(iostream->input, STDIN_FILENO);
	if (iostream->output != -1)
		dup2(iostream->output, STDOUT_FILENO);
	if (command->token == BUILTIN)
	{
		get_builtin(command->string, iostream, iostream->env);
		exit(0);
	}
	else
	{
		env_from_ll = ll_to_2d_arr(*iostream->env);
		paths = get_path(env_from_ll);
		cmd = set_valid_command(iostream->args[0], paths);
		if (!cmd)
			print_cmd_err(iostream->args[0]);
		execve(cmd, iostream->args, env_from_ll);
		exit(127);
	}
}
