/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executing_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:09:47 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/11 12:41:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_last_cmd(t_cmd_data **data, t_stream **iostream)
{
	close((*iostream)->pipes->curr_write);
	init_stream(iostream);
	trim_command(data, true);
	return (1);
}

int	status_and_clean(t_cmd_data **data, t_stream **iostream, int *status,
		int *pid)
{
	if ((*iostream)->file_failure)
	{
		clean_all(data, *iostream, (*data)->total_pipes);
		return (*status);
	}
	*status = wait_for_processes(*pid, (*data)->wait_total);
	clean_all(data, *iostream, (*data)->total_pipes);
	return (check_status(*status));
}

int	do_exit(t_stream *iostream, bool *exit_called)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = -1;
	if (check_if_valid_exit(iostream->args))
		*exit_called = true;
	pid = fork();
	if (pid == 0)
	{
		status = get_exit(*iostream->env, iostream->args);
		exit(status);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

int	check_parent_builtin(char *str)
{
	if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	else
		return (0);
}

void	clean_single_cmd(t_cmd_data *data, t_stream *iostream, int count)
{
	if (*(data)->command)
		free_ll_command(*(data)->command, true);
	if (iostream)
		free_iostream(&iostream, count);
	if (data)
		free(data);
}
