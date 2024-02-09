#include "libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
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
}						TOKEN;

typedef struct s_pipes
{
	int					curr_write;
	int					curr_read;
	int					prev_write;
	int					prev_read;
}						t_pipes;

typedef struct s_stream
{
	char				**args;
	char				**PATH;
	int					input;
	int					output;
	t_pipes				*pipes;

}						t_stream;

typedef struct token_redirect
{
	int					fd;
}						token_redirect;

typedef struct t_command
{
	char				**arguments;
	char				*string;
	char				*command_path;
	char				**envp;
	int					pipe;
	int8_t				token;
	struct t_command	*next;

}						t_command;

/*
BUILTINS
*/
void					cd(char *directory, t_env_ll *env);
void					echo(char *msg, int n);
void					get_env(char **env);
char					**export(char **env, char *export_data);
char					*pwd(char **env);
char					**unset(char **env, char *unset_data);

/*
EXECUTING
*/
void					execute(t_command **param, t_stream *iostream);
void					execute_single(t_command **param, t_stream *iostream);

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

/*
UTILS / PARSER_UTILS
*/
char					**get_path(char **envp);
int						pipe_check(t_command *command);
t_command				*get_command_from_pipe(t_command *command);
t_command				*get_command_until_pipe(t_command *command);

/*
UTILS / STATUS
*/
int						check_status(int status);

/*
UTILS / PRINT
*/
void					print_list(t_command *command);
void					print_2d_arrg(char **c);
void					print_env_ll(t_env_ll *env);