/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 09:48:00 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 09:49:15 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
