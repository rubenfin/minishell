/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 18:11:33 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/06 12:02:12 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

sig_atomic_t	signal_status;

void	handle_signals_normal(int sig)
{
	if (sig == SIGINT)
	{
		signal_status = 130;
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
		signal_status = 130;
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals_cmd(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
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
