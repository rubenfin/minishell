/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 15:38:30 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/14 16:59:35 by rfinneru      ########   odam.nl         */
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

int	minishell(int ac, char **av, char **envp)
{
	t_env_ll	*env;
	char		*buffer;
    int fd_stdin = dup(STDIN_FILENO);
	make_env_ll(&env, envp);
	// 	char	*prompt;
	(void)ac;
	(void)av;
	while (1)
	{
		// prompt = find_curr_pwd(env);
        dup2(fd_stdin, STDIN_FILENO);
		buffer = readline("~$ ");
		if (!buffer)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (buffer && !ft_strncmp(buffer, "exit", 5))
		{
			write(1, "exit\n", 6);
			break ;
		}
		command_line(env, buffer);
		if (buffer && ft_strlen(buffer) > 0)
			add_history(buffer);
		free(buffer);
		buffer = NULL;
        // rl_on_new_line()
		// free(prompt);
	}
	free(buffer);
	printf("werkt");
	// free(prompt);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	signal(SIGINT, handle_sigint);
	if (ac == 1)
	{
		return (minishell(ac, av, envp));
	}
	else
		return (printf("usage: ./minishell\n"), EXIT_FAILURE);
	return (0);
}