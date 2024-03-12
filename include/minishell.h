/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 12:01:35 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 16:05:45 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_signal_status;

typedef struct s_env_ll
{
	char						*key;
	char						*value;
	struct s_env_ll				*prev;
	struct s_env_ll				*next;
}								t_env_ll;

typedef enum SIGNALS
{
	NORMAL,
	HERE_DOC,
	RUNNING_CMD,
}								t_SIGNALS;

typedef enum TOKEN
{
	CMD,
	RE_IN,
	RE_OUT,
	RE_HERE,
	RE_APPEND,
	PIPE,
	BUILTIN,
}								t_TOKEN;

typedef struct s_std_fd
{
	int							stdin_fd;
	int							stdout_fd;
	int							stderr_fd;
}								t_std_fd;

typedef struct s_pipes
{
	int							curr_write;
	int							curr_read;
	int							prev_write;
	int							prev_read;
}								t_pipes;

typedef struct s_stream
{
	t_env_ll					**env;
	char						**args;
	bool						file_failure;
	int							input;
	int							output;
	t_pipes						*pipes;
	int							prev_exit_status;
}								t_stream;

typedef struct t_command
{
	char						*string;
	int8_t						token;
	struct t_command			*next;

}								t_command;

typedef struct s_basic_cmd
{
	t_command					**command;
	t_command					*one_cmd;
	t_command					*cmds_left;
	int							total_pipes;
	int							wait_total;
}								t_cmd_data;

int								parser(t_env_ll **env, t_command **command,
									char *buffer, int status);
int								command_line(t_env_ll **env,
									t_command **command, bool *exit);

/*
BUILTINS
*/
int								cd(t_env_ll **env, char **directory);
void							echo(t_env_ll *env, char **args);
int								get_env(t_env_ll **env, char **args);
int								export(t_env_ll **env, char **export_data);
int								pwd(t_env_ll *env);
int								unset(t_env_ll **env, char **unset_data);
int								get_exit(t_env_ll *env, char **args);

/*
EXECUTING
*/
int								set_redirections(t_command **param,
									t_stream *iostream, bool child, int *pid);
int								execute(t_command **param, t_stream *iostream);
int								get_builtin(char *command, t_stream *param,
									t_env_ll **env);
int								check_if_valid_exit(char **args);

int								setup_cmds(t_cmd_data **data,
									t_command **command);
int								setup_before_executing(t_cmd_data **data,
									t_env_ll **env, t_command **command,
									t_stream **iostream);
int								trim_command(t_cmd_data **data, bool last_cmd);
int								clean_cmd_leftovers(t_cmd_data **data,
									t_stream **iostream);
int								setup_last_cmd(t_cmd_data **data,
									t_stream **iostream);
int								status_and_clean(t_cmd_data **data,
									t_stream **iostream, int *status, int *pid);
int								do_exit(t_stream *iostream, bool *exit_called);
int								check_parent_builtin(char *str);
void							clean_single_cmd(t_cmd_data *data,
									t_stream *iostream, int count);
int								wait_for_processes(int pid, int wait_total);
int								redirection_here(t_stream *iostream,
									t_command *command);
int								redirection_in(t_stream *iostream,
									t_command *cmd);
int								redirection_out(t_stream *iostream,
									t_command *cmd);
int								redirection_append(t_stream *iostream,
									t_command *cmd);
int								return_right_status(bool *exit_called, int pid,
									int status);
int								last_slash(char *str);
int								go_prev(t_env_ll **env);
int								go_back(t_env_ll **env, char *directory);
int								go_home(t_env_ll **env, char *directory);
int								plus_or_min(char **args, int i, int j);
/*
PARSING
*/
int								createnode(t_command **head, char *data,
									int redirection);
t_command						*createnode_return(t_command **head, char *data,
									int redirection);

char							*set_valid_command(char *argv,
									char **full_path);
int								init_redirections(char *str, t_command **param,
									t_env_ll **env, int status);
int								make_env_ll(t_env_ll **env, char **envp);
t_env_ll						*find_key(t_env_ll *env, char *key_str);
t_env_ll						*find_value(t_env_ll *env, char *value_str);
void							put_node_at_end(t_env_ll **env,
									t_env_ll **node);
char							*expanding(char *result, t_env_ll **env,
									int status);
int								empty_checker(char *str);
int								redirection_checker_int(char *str, int i,
									int check_all);
int								redirection_checker_bool(char *str, int i,
									int check_all);
int								check_first_cmd(char *str, int i);
int								dollar_sign_check(char *result);
int								check_closing_quote_with_quote(char *str,
									char quote);
int								check_closing_quote(char *str);
int								check_starting_quote(char *str);
int								quote_counter(const char *str, int quote);
int								total_quote(const char *str);
int								dollar_count(char *str);
int								find_end_sign(char *str);
char							*find_until_dollar(char *str);
char							*find_key_return_value_expanding(t_env_ll *env,
									char *key_str, int status);
/*
SIGNALS
*/
void							handle_signals_normal(int sig);
void							handle_signals_heredoc(int sig);
void							send_signals(t_SIGNALS SIGNAL);

/*
UTILS / INITIALIZNG
*/
int								init_stream_pipes(t_stream **iostream);
int								init_pipe(t_pipes *pipes);
void							init_stream(t_stream **iostream);
int								check_builtin(char *arg);
int								malloc_stream(t_stream **iostream,
									t_env_ll **env);
void							set_args(t_command **param, t_stream *iostream,
									int count);
int								refresh_std_fd(t_std_fd *std_fd);
int								init_std_fd(t_std_fd **std_fd);
/*
UTILS / PARSER_UTILS
*/
char							**get_path(char **envp);
int								pipe_check(t_command *command);
t_command						*get_command_from_pipe(t_command *command);
t_command						*get_command_until_pipe(t_command *command);
char							*ft_strndup(char *s, size_t n);
char							**ll_to_2d_arr(t_env_ll *env);
int								count_commands(t_command **param);
/*
UTILS / STATUS
*/
int								check_status(int status);
void							close_pipes(t_pipes *pipes);
int								set_file_failure_return(t_stream *iostream);
/*
UTILS / PRINT
*/
void							print_list(t_command *command);
void							print_2d_arrg(char **c);
void							print_env_ll(t_env_ll *env);
void							print_export(t_env_ll *env);

/*
UTILS / CLEAN
*/
void							ft_free(char **buffer);
void							free_ll(t_env_ll **env);
void							free_ll_command(t_command *head,
									bool main_command);
void							free_args(char **args);
void							free_iostream(t_stream **iostream, int count);
void							clean_all(t_cmd_data **data, t_stream *iostream,
									int total_pipes);
/*
UTILS / PRINT ERROR
*/
void							print_cmd_err(char *cmd);
void							print_file_dir_err(char *dir, bool cd);
void							print_exit_err(char *buffer, bool numeric);
void							pr_invalid(t_env_ll **node, char **export_data,
									int j);
void							print_hd_err(char *limiter);
void							print_file_permission_err(char *file);
void							cd_lost_parent_err(void);
void							syntax_error(void);
void							print_dup_err(void);

/*
UTILS / BUILTINS UTILS
*/
void							change_pwd(t_env_ll **env, char *change_value);
char							*find_key_return_value(t_env_ll *env,
									char *key_str);
void							get_key_change_value(t_env_ll **env,
									char *key_str, char *change_value);
void							find_key_free_value(t_env_ll **env,
									char *key_str);
char							*find_value_char(t_env_ll *env, char *value_str,
									int *i, int status);
int								max(int a, int b);

int								dir_check(char *argv);
void							check_dir_exe(char *argv);
int								valid_identifier_check(char c);
char							*get_curr_dir(void);

/*
UTILS / FD_HANDLING
*/
int								close_std_fds(t_std_fd *std_fd);
