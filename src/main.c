/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 15:38:30 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/14 19:59:52 by rfinneru      ########   odam.nl         */
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

int	minishell(t_env_ll *env)
{
	char	*buffer;
	int		fd_stdin;
	int		status;

	status = 0;
	fd_stdin = dup(STDIN_FILENO);
	// char	*prompt;
	while (1)
	{
		dup2(fd_stdin, STDIN_FILENO);
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
	ft_free(&buffer);
	// free(prompt);
	return (write(1, "exit\n", 5), status);
}

int	main(int ac, char **av, char **envp)
{
	t_env_ll	*env;
	int			status;

	status = 0;
	signal(SIGINT, handle_sigint);
	if (ac == 1)
	{
		make_env_ll(&env, envp);
		status = minishell(env);
		free_ll(env);
		return (status);
	}
	else
		return (printf("usage: ./minishell\n"), EXIT_FAILURE);
	return (0);
}
