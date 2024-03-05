
#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	minishell(t_env_ll **env, t_std_fd *std_fd)
{
	char	*buffer;
	int		status;
	bool	exit;

	exit = false;
	status = 0;
	while (1)
	{
		refresh_std_fd(std_fd);
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
		printf("last command status %d\n", status);
	}
	rl_clear_history();
	ft_free(&buffer);
	return (write(1, "exit\n", 5), status);
}

int	main(int ac, char **av, char **envp)
{
	t_env_ll	*env;
	t_std_fd	*std_fd;
	int			status;

	status = 0;
	(void)av;
	signal(SIGINT, handle_sigint);
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
