/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 18:11:33 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 10:41:19 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal_status;

void	handle_signals_normal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal_status != 130)
		{
			g_signal_status = 130;
			close(STDIN_FILENO);
			write(STDOUT_FILENO, "\n", 1);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals_cmd(int sig)
{
	kill(0, sig);
}

void	send_signals(t_SIGNALS SIGNAL)
{
	signal(SIGQUIT, SIG_IGN);
	if (SIGNAL == RUNNING_CMD)
		signal(SIGINT, handle_signals_cmd);
	else if (SIGNAL == HERE_DOC)
		signal(SIGINT, handle_signals_heredoc);
	else
		signal(SIGINT, handle_signals_normal);
}
