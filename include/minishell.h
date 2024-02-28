#include "libft.h"
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
#include <unistd.h>

typedef struct s_env_ll
{
	char				*key;
	char				*value;
	struct s_env_ll		*prev;
	struct s_env_ll		*next;
}						t_env_ll;

typedef enum TOKEN
{
	CMD,
	RE_IN,
	RE_OUT,
	RE_HERE,
	RE_APPEND,
	PIPE,
	BUILTIN,
}						TOKEN;

// typedef struct s_general
// {
// 	int					prev_exit_status;
// 	bool				has_exit_been_called;
// }						t_general;

typedef struct s_std_fd
{
	int					stdin_fd;
	int					stdout_fd;
}						t_std_fd;

typedef struct s_pipes
{
	int					curr_write;
	int					curr_read;
	int					prev_write;
	int					prev_read;
}						t_pipes;

typedef struct s_stream
{
	t_env_ll			**env;
	char				**args;
	bool				file_failure;
	int					input;
	int					output;
	t_pipes				*pipes;
	int					prev_exit_status;
}						t_stream;

typedef struct t_command
{
	char				*string;
	int8_t				token;
	struct t_command	*next;

}						t_command;

int						command_line(t_env_ll **env, char *arg, int exit_status,
							bool *exit);

/*
BUILTINS
*/
int						cd(t_env_ll **env, char *directory);
void					echo(t_env_ll *env, char **args);
int						get_env(t_env_ll **env, char **args);
int						export(t_env_ll **env, char **export_data);
int						pwd(t_env_ll *env);
int						unset(t_env_ll **env, char **unset_data);
int						get_exit(t_env_ll *env, char **args);

/*
EXECUTING
*/
int						execute(t_command **param, t_stream *iostream,
							bool child, int *pid);
void					execute_single(t_command **param, t_stream *iostream);
int						get_builtin(char *command, t_stream *param,
							t_env_ll **env);
int						check_if_valid_exit(char **args);

/*
PARSING
*/
t_command				*createnode(t_command **head, char *data,
							int redirection);
char					*set_valid_command(char *argv, char **full_path);
t_command				*init_redirections(char *str, t_command **param);
void					make_env_ll(t_env_ll **env, char **envp);
t_env_ll				*find_key(t_env_ll *env, char *key_str);
t_env_ll				*find_value(t_env_ll *env, char *value_str);
/*
UTILS / INITIALIZNG
*/
int						init_pipe(t_pipes *pipes);
void					init_stream(t_stream **iostream);
int						check_builtin(char *arg);
void					malloc_stream(t_stream **iostream, t_env_ll **env);
void					set_args(t_command **param, t_stream *iostream,
							int count);
void					refresh_std_fd(t_std_fd *std_fd);
void					init_std_fd(t_std_fd **std_fd);
/*
UTILS / PARSER_UTILS
*/
char					**get_path(char **envp);
int						pipe_check(t_command *command);
t_command				*get_command_from_pipe(t_command *command);
t_command				*get_command_until_pipe(t_command *command);
char					*ft_strndup(char *s, size_t n);
char					**ll_to_2d_arr(t_env_ll *env);
int						count_commands(t_command **param);
/*
UTILS / STATUS
*/
int						check_status(int status);
void					close_pipes(t_pipes *pipes);
int						set_file_failure_return(t_stream *iostream);
/*
UTILS / PRINT
*/
void					print_list(t_command *command);
void					print_2d_arrg(char **c);
void					print_env_ll(t_env_ll *env);

/*
UTILS / CLEAN
*/
void					ft_free(char **buffer);
void					free_ll(t_env_ll **env);
void					free_ll_command(t_command *head, bool main_command);
void					free_args(char **args);
void					free_iostream(t_stream **iostream, int count);
void					free_all_close_pipes(t_command *saved,
							t_command *until_pipe, t_stream *iostream,
							int total_pipes);

/*
UTILS / PRINT ERROR
*/
void					print_cmd_err(char *cmd);
void					print_file_dir_err(char *dir);
void					print_exit_err(char *buffer, bool numeric);

/*
UTILS / BUILTINS UTILS
*/
void					change_pwd(t_env_ll **env, char *change_value);
char					*find_key_return_value(t_env_ll *env, char *key_str);
void					get_key_change_value(t_env_ll **env, char *key_str,
							char *change_value);
void					find_key_free_value(t_env_ll **env, char *key_str);
int						max(int a, int b);