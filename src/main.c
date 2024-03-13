/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 11:47:31 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/13 10:55:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	clear_history_close_fds(t_std_fd *std_fd, char **buffer)
{
	rl_clear_history();
	ft_free(buffer);
	if (!close_std_fds(std_fd))
		return (0);
	return (1);
}

void	add_to_history_clr_buffer(char **buffer)
{
	if (*buffer && ft_strlen(*buffer) > 0)
		add_history(*buffer);
	ft_free(buffer);
}

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

	exit = false;
	status = 0;
	parsed = NULL;
	while (1)
	{
		buffer = setup_rl_and_sig(&status);
		if (!buffer)
			break ;
		if (!parser(env, &parsed, buffer, status))
			continue ;
		status = command_line(env, &parsed, &exit);
		add_to_history_clr_buffer(&buffer);
		if (!check_signal_fds_exit(exit, &status, std_fd))
			break ;
		printf("exit status: %d\n", status);
	}
	clear_history_close_fds(std_fd, &buffer);
	return (write(1, "exit\n", 5), status);
}

int	set_tty_settings(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (0);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (0);
	return (1);
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
		printf("exited with %d\n", status);
		free_ll(&env);
		free(std_fd);
		return (status);
	}
	else
		return (write(STDERR_FILENO, "usage: ./minishell\n", 19), EXIT_FAILURE);
}
