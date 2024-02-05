/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 12:47:21 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/05 13:45:59 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_curr_pwd(char **env)
{
	char	*curr_pwd;
	char	*curr_pwd2;
	int		i;
	int		x;
	int		length;
	int		y;
	int		count;

	count = 0;
	y = 0;
	i = 0;
	x = 0;
	length = 0;
	while (!ft_strnstr(env[i], "PWD", 3))
		i++;
	while (env[i][x] != '/' || count != 2)
	{
		if (env[i][x] == '/')
			count++;
		x++;
	}
	x++;
	while (env[i][x])
	{
		x++;
		length++;
	}
	x = x - length;
	curr_pwd = malloc(length * sizeof(char));
	while (env[i][x])
	{
		curr_pwd[y] = env[i][x];
		y++;
		x++;
	}
	curr_pwd2 = ft_strjoin("~/", curr_pwd);
	free(curr_pwd);
	curr_pwd = NULL;
	curr_pwd = ft_strjoin(curr_pwd2, "$ ");
	free(curr_pwd2);
	return (curr_pwd);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	check_input(char *input, char ***env)
{
	if (!ft_strncmp(input, "cd", 3))
		cd("/test", *env);
	else if (!ft_strncmp(input, "pwd", 4))
		pwd(*env);
	else if (!ft_strncmp(input, "echo", 5))
		echo("test$PATH", 0);
	else if (!ft_strncmp(input, "echo -n", 8))
		echo("test", 1);
	else if (!ft_strncmp(input, "env", 3))
		get_env(*env);
	else if (!ft_strncmp(input, "export", 6))
		*env = export(*env, "EXPORT=test");
	else if (!ft_strncmp(input, "unset", 5))
		*env = unset(*env, "PWD");
}

int	minishell(int ac, char **av, char **env)
{
	char	*buffer;

	// 	char	*prompt;
	(void)ac;
	(void)av;
	while (1)
	{
		// prompt = find_curr_pwd(env);
		buffer = readline("~$ ");
		rl_on_new_line();
		if (!buffer)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!ft_strncmp(buffer, "exit", 5))
		{
			write(1, "exit\n", 5);
			break ;
		}
		check_input(buffer, &env);
		if (ft_strlen(buffer) > 0)
			add_history(buffer);
		free(buffer);
		// free(prompt);
	}
	free(buffer);
	// free(prompt);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char **my_own_env;
	signal(SIGINT, handle_sigint);
	if (ac == 1)
	{
		my_own_env = make_my_env(env);
		return (minishell(ac, av, my_own_env));
	}
	else
		return (printf("usage: ./minishell\n"), EXIT_FAILURE);
	return (0);
}