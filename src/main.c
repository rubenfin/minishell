
#include "../include/minishell.h"

int	minishell(t_env_ll **env, t_std_fd *std_fd)
{
	char	*buffer;
	int		status;
	bool	exit;

	exit = false;
	status = 0;
	while (1)
	{
		send_signals(NORMAL);
		signal_status = -1;
		buffer = readline("~$: ");
		rl_on_new_line();
		if (!buffer)
			break ;
		status = command_line(env, buffer, status, &exit);
		if (buffer && ft_strlen(buffer) > 0)
			add_history(buffer);
		ft_free(&buffer);
		if (exit)
			break ;
		if (signal_status != -1)
			status = signal_status;
		refresh_std_fd(std_fd);
	}
	rl_clear_history();
	ft_free(&buffer);
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
		close(std_fd->stderr_fd);
		close(std_fd->stdin_fd);
		close(std_fd->stdout_fd);
		free(std_fd);
		return (status);
	}
	else
		return (write(STDERR_FILENO, "usage: ./minishell\n", 19), EXIT_FAILURE);
}
