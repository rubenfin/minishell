/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 16:36:54 by jade-haa      #+#    #+#                 */
/*   Updated: 2024/03/05 17:02:43 by rfinneru      ########   odam.nl         */
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
	else if (ft_strncmp(arg, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(arg, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(arg, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(arg, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(arg, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(arg, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

int	get_builtin(char *command, t_stream *param, t_env_ll **env)
{
	char	**args;

	args = param->args;
	if (ft_strncmp(command, "echo", 5) == 0)
		return (echo(*env, args), 0);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (cd(env, args));
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (pwd(*env));
	else if (ft_strncmp(command, "export", 7) == 0)
		return (export(env, args));
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (unset(env, args));
	else if (ft_strncmp(command, "env", 4) == 0)
		return (get_env(env, args));
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (get_exit(*env, args));
	else
		return (127);
}

void	else_statement(t_stream *iostream)
{
	char	**env_from_ll;
	char	**paths;
	char	*cmd;

	check_dir_exe(iostream->args[0]);
	env_from_ll = ll_to_2d_arr(*iostream->env);
	if (!env_from_ll)
		exit(EXIT_FAILURE);
	paths = get_path(env_from_ll);
	cmd = set_valid_command(iostream->args[0], paths);
	if (!cmd)
	{
		free_args(paths);
		free_args(env_from_ll);
		print_cmd_err(iostream->args[0]);
	}
	execve(cmd, iostream->args, env_from_ll);
	free(cmd);
	free_args(paths);
	free_args(env_from_ll);
	exit(127);
}

void	ft_dup2(int iostream, int standard)
{
	if (dup2(iostream, standard) == -1)
		exit(errno);
}

int	execute_single(t_command **param, t_stream *iostream)
{
	t_command	*command;
	int			count;

	command = *param;
	if (command->token == PIPE)
		command = command->next;
	count = count_commands(&command);
	iostream->args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!iostream->args)
		return (-1);
	set_args(param, iostream, count);
	if (iostream->input != -1)
		ft_dup2(iostream->input, STDIN_FILENO);
	if (iostream->output != -1)
		ft_dup2(iostream->output, STDOUT_FILENO);
	if (command->token == BUILTIN)
		exit(get_builtin(command->string, iostream, iostream->env));
	else
		else_statement(iostream);
	return (1);
}
