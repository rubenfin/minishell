#include "libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// #define CMD 0
// #define RE_IN 1
// #define RE_OUT 2
// #define RE_HERE 3
// #define RE_APPEND 4
// #define PIPE 5

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
