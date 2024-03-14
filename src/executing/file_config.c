/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_config.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 13:59:14 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/14 09:04:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/minishell.h"

int	here_doc(t_command *command, char **str, char **limiter)
{
	char	*buffer;

	buffer = NULL;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		send_signals(HERE_DOC);
		write(STDOUT_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer || !ft_strncmp(buffer, *limiter, ft_strlen(*limiter)))
		{
			if (!buffer)
				print_hd_err(command->string);
			ft_free(&buffer);
			break ;
		}
		*str = ft_strjoin_gnl(*str, buffer);
		ft_free(&buffer);
		if (!*str)
		{
			ft_free(limiter);
			return (0);
		}
	}
	return (1);
}

int	redirection_here(t_stream *iostream, t_command *command)
{
	int		fd;
	char	*limiter;
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (set_file_failure_return(iostream));
	limiter = ft_strjoin(command->string, "\n");
	if (!limiter)
		return (ft_free(&str), set_file_failure_return(iostream));
	fd = open("objs/utils/.hd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_free2(&limiter, &str), set_file_failure_return(iostream));
	if (!here_doc(command, &str, &limiter))
		return (ft_free2(&limiter, &str), set_file_failure_return(iostream));
	write(fd, str, ft_strlen(str));
	close(fd);
	iostream->input = open("objs/utils/.hd", O_RDONLY);
	if (iostream->input == -1)
		return (ft_free2(&limiter, &str), set_file_failure_return(iostream));
	ft_free(&str);
	ft_free(&limiter);
	return (EXIT_SUCCESS);
}

int	redirection_in(t_stream *iostream, t_command *cmd)
{
	if (access(cmd->string, F_OK) == -1)
	{
		print_file_dir_err(cmd->string, false);
		return (set_file_failure_return(iostream));
	}
	if (access(cmd->string, R_OK) == -1)
	{
		print_file_permission_err(cmd->string);
		return (set_file_failure_return(iostream));
	}
	iostream->input = open(cmd->string, O_RDONLY);
	if (iostream->input == -1)
	{
		print_file_dir_err(cmd->string, false);
		return (set_file_failure_return(iostream));
	}
	return (EXIT_SUCCESS);
}

int	redirection_out(t_stream *iostream, t_command *cmd)
{
	if (access(cmd->string, F_OK) == 0 && access(cmd->string, W_OK) == -1)
	{
		print_file_permission_err(cmd->string);
		return (set_file_failure_return(iostream));
	}
	iostream->output = open(cmd->string, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (iostream->output == -1)
	{
		print_file_dir_err(cmd->string, false);
		return (set_file_failure_return(iostream));
	}
	return (EXIT_SUCCESS);
}

int	redirection_append(t_stream *iostream, t_command *cmd)
{
	if (access(cmd->string, F_OK) == 0 && access(cmd->string, W_OK) == -1)
	{
		print_file_permission_err(cmd->string);
		return (set_file_failure_return(iostream));
	}
	iostream->output = open(cmd->string, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (iostream->output == -1)
	{
		print_file_dir_err(cmd->string, false);
		return (set_file_failure_return(iostream));
	}
	return (EXIT_SUCCESS);
}
