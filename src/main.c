/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 15:38:30 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/17 10:48:15 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	minishell(t_env_ll *env, t_std_fd *std_fd)
{
	char	*buffer;
	int		status;

	status = 0;
	// char	*prompt;
	while (1)
	{
		refresh_std_fd(std_fd);
		printf("last cmd exit status:%d\n", status);
		buffer = readline("~$ ");
		rl_on_new_line();
		if (!buffer)
			break ;
		if (buffer && !ft_strncmp(buffer, "exit", 5))
			break ;
		status = command_line(env, buffer);
		if (buffer && ft_strlen(buffer) > 0)
			add_history(buffer);
		ft_free(&buffer);
		// free(prompt);
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
		init_std_fd(&std_fd);
		make_env_ll(&env, envp);
		status = minishell(env, std_fd);
		free_ll(env);
		free(std_fd);
		return (status);
	}
	else
		return (printf("usage: ./minishell\n"), EXIT_FAILURE);
	return (0);
}
