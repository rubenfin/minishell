/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 18:11:33 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 15:23:44 by rfinneru      ########   odam.nl         */
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
}

void	handle_signals_cmd(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		g_signal_status = 131;
	}
}

void	send_signals(t_SIGNALS SIGNAL)
{
	if (SIGNAL == RUNNING_CMD)
	{
		signal(SIGQUIT, handle_signals_cmd);
		signal(SIGINT, handle_signals_cmd);
	}
	else if (SIGNAL == HERE_DOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals_heredoc);
	}
	else if (SIGNAL == NORMAL)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals_normal);
	}
}
