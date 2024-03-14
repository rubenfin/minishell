/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 11:47:31 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 14:57:29 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*setup_rl_and_sig(int *status)
{
	char	*buffer;

	g_signal_status = -1;
	send_signals(NORMAL);
	buffer = readline("~$: ");
	rl_on_new_line();
	if (g_signal_status != -1)
		*status = g_signal_status;
	return (buffer);
}

int	check_signal_fds_exit(bool exit, int *status, t_std_fd *std_fd)
{
	if (exit)
		return (0);
	if (g_signal_status != -1)
		*status = g_signal_status;
	if (!refresh_std_fd(std_fd))
		return (0);
	return (1);
}

int	minishell(t_env_ll **env, t_std_fd *std_fd)
{
	t_command	*parsed;
	char		*buffer;
	int			status;
	bool		exit;

	buffer = NULL;
	exit = false;
	status = 0;
	parsed = NULL;
	while (1)
	{
		buffer = setup_rl_and_sig(&status);
		if (!buffer)
			break ;
		if (!parser(env, &parsed, &buffer, status))
			continue ;
		status = command_line(env, &parsed, &exit);
		if (!check_signal_fds_exit(exit, &status, std_fd))
			break ;
	}
	clear_history_close_fds(std_fd, &buffer);
	return (write(1, "exit\n", 5), status);
}

int	main(int ac, char **av, char **envp)
{
	t_env_ll	*env;
	t_std_fd	*std_fd;
	int			status;

	status = 0;
	(void)av;
	if (!set_tty_settings())
		return (EXIT_FAILURE);
	if (ac == 1)
	{
		if (init_std_fd(&std_fd) == -1)
			exit(EXIT_FAILURE);
		if (make_env_ll(&env, envp) == -1)
			exit(EXIT_FAILURE);
		status = minishell(&env, std_fd);
		free_ll(&env);
		free(std_fd);
		return (status);
	}
	else
		return (write(STDERR_FILENO, "usage: ./minishell\n", 19), EXIT_FAILURE);
}
