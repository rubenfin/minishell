/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 12:47:39 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/05 13:43:09 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_minishell
{
	int					TOKEN;
	char				*text;
	struct s_minishell	*next;
	struct s_minishell	*prev;
}						t_minishell;

/*
BUILTINS
*/
void					cd(char *directory, char **env);
void					echo(char *msg, int n);
char					*pwd(char **env);
void					get_env(char **env);
char					**export(char **env, char *export_data);
char					**unset(char **env, char *unset_data);

/*
MAKING OWN ENV
*/
char					**make_my_env(char **env);
char					**malloc_my_own_env(char **env,
							char **making_my_own_env);

/*
HELPERS DEBUG
*/
void					print_2d_arr(char **c);

#endif