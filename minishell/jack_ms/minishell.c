#include "minishell.h"

// t_command	*createnode(t_command **head)
// {
// 	t_command	*newnode;

// 	newnode = (t_command *)malloc(sizeof(t_command));
// 	if (!newnode)
// 		return (NULL);
// 	newnode->next = NULL;
// 	if (*head == NULL)
// 	{
// 		*head = newnode;
// 	}
// 	else
// 	{
// 		newnode->next = *head;
// 		*head = newnode;
// 	}
// 	printf("werkt");
// 	return (newnode);
// }

t_command	*createnode(t_command **head, char *data, int redirection)
{
	t_command	*newnode;
	t_command	*temp;

	newnode = (t_command *)malloc(sizeof(t_command));
	if (!newnode)
	{
		return (NULL);
	}
	newnode->string = data;
	newnode->token = redirection;
	newnode->next = NULL;
	if (*head == NULL)
	{
		*head = newnode;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newnode;
	}
	return (newnode);
}
int	directions_checker_int(char *str, int i, int check_all)
{
	if (check_all)
	{
		if (ft_strncmp(&str[i], "|", 1) == 0)
			return (5);
	}
	if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (RE_APPEND);
	if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (RE_HERE);
	if (ft_strncmp(&str[i], "<", 1) == 0)
		return (RE_IN);
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (RE_OUT);
	return (0);
}

int	directions_checker_bool(char *str, int i, int check_all)
{
	if (check_all)
	{
		if (ft_strncmp(&str[i], "|", 1) == 0)
			return (1);
	}
	if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (1);
	if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (1);
	if (ft_strncmp(&str[i], "<", 1) == 0)
		return (1);
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (1);
	return (0);
}
int	length_command(char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (0);
	while (command[i] && command[i] != ' ')
		i++;
	return (i + 1);
}

// int	count_arguments(char **split, int i)
// {
// 	int	counter;

// 	// int	i;
// 	// i = 1;
// 	counter = 1;
// 	while (split[i] && !directions_checker(split, i, 0))
// 	{
// 		++counter;
// 		++i;
// 	}
// 	return (counter);
// }
char	*find_flag(char *command)
{
	int		i;
	int		j;
	char	*flag;

	i = 0;
	// if (command[i] != '-')
	// 	return(NULL);
	if (!command[i])
		return (NULL);
	// i++;
	j = i;
	while (command[j])
		j++;
	flag = malloc(j * sizeof(char) + 1);
	if (!flag)
		return (NULL);
	j = 0;
	while (command[i])
		flag[j++] = command[i++];
	flag[j] = '\0';
	return (flag);
}

char	**get_path(char **envp)
{
	int		i;
	char	*path_string;
	char	**result_string;

	path_string = NULL;
	i = 0;
	while (!path_string)
	{
		path_string = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	result_string = ft_split(path_string, ':');
	if (!result_string)
		exit(1);
	return (result_string);
}

int	valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc(len * sizeof(char));
	if (!trimmed_command)
		return (0);
	ft_strlcpy(trimmed_command, argv, len);
	j = 0;
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (0);
		free(temp);
		if (access(str, X_OK) == 0)
			return (1);
		free(str);
		j++;
	}
	free(trimmed_command);
	return (0);
}

char	*set_valid_command(char *argv, char **full_path)
{
	int		j;
	char	*str;
	size_t	len;
	char	*trimmed_command;
	char	*temp;

	len = length_command(argv);
	trimmed_command = (char *)malloc(len * sizeof(char));
	if (!trimmed_command)
		return (0);
	ft_strlcpy(trimmed_command, argv, len);
	j = 0;
	while (full_path[j])
	{
		temp = ft_strjoin(full_path[j], "/");
		str = ft_strjoin(temp, trimmed_command);
		if (!temp | !str)
			return (NULL);
		free(temp);
		if (access(str, X_OK) == 0)
			break ;
		free(str);
		j++;
	}
	free(trimmed_command);
	return (str);
}

int	arg_counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*quote_check(char *str)
{
	int	x;
	int	i;

	i = 0;
	x = i + 1;
	++i;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			break ;
		++i;
	}
	// *param = i;
	return (ft_substr(str, x, i - x));
}

void	check_command(t_command **command, char *str)
{
}

t_command	*init_redirections(char *str, t_command **param, char **path)
{
	int			i;
	t_command	*command;
	int			len;
	int			redirection;
	char		*result;

	i = 0;
	command = *param;
	while (str[i])
	{
		redirection = CMD;
		len = 0;
		while (str[i] && (str[i] == ' ' || directions_checker_bool(&str[i], 0,
					0)))
		{
			if (directions_checker_bool(&str[i], 0, 0) && redirection == CMD)
				redirection = directions_checker_int(&str[i], 0, 0);
			++i;
		}
		if (ft_strncmp(&str[i], "|", 1) == 0)
			redirection = PIPE;
		// if (str[i] == '\"' || str[i] == '\'')
		// 	result = quote_check(&str[i]);
		// else
		// {
		while (str[i + len] && (str[i + len] != ' '))
		{
			++len;
			if (redirection == PIPE || directions_checker_bool(&str[i + len], 0,
					1))
				break ;
			// printf("%d\n", redirection);
		}
		// }
		if (len > 0)
		{
			result = ft_substr(&str[i], 0, len);
			command = createnode(param, result, redirection);
			printf("command: %s\n", command->string);
			printf("Token : %d\n\n", command->token);
			// check_string(&command, str, redirection);
		}
		i += len;
	}
	return (command);
}

char	**get_all_commands(t_command *command)
{
	char		**all_commands;
	t_command	*total_commands;
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (total_commands || !total_commands->token == PIPE)
	{
		if (total_commands->token == CMD)
			count++;
	}
	all_commands = (char **)malloc((count + 1) * sizeof(char *));
	while (command || !command->token == PIPE)
	{
		if (command->token == CMD)
		{
			all_commands[i] = ft_strdup(command->string);
			i++;
		}
	}
	return(all_commands);
}

void	child_one(int *fd, t_command *command, char **path)
{
	int			infile;
	int			flag;
	t_command	*get_token;
	t_command	*get_fd;
	char		**command;

	get_token = command;
	get_fd = command;
	flag = -1;
	while (get_token && !get_token->token == PIPE)
	{
		if (get_token->token == 1 || get_token->token == 3)
			flag = command->token;
		get_token = get_token->next;
	}
	if (flag > 0)
	{
		while (!get_fd->token == 1 && !get_fd->token == 3)
			get_fd = get_fd->next;
		if (access(get_fd->string, F_OK) == -1 || access(get_fd->string,
				R_OK) == -1)
		{
			perror("infile not found");
			exit(EXIT_FAILURE);
		}
		infile = open(get_fd->string, O_RDONLY);
		if (infile == -1)
			exit(EXIT_FAILURE);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else
	{
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	command = get_all_commands(command);
	find_path(argv[2], envp);
}

void	child_two(int *fd, char *argv[], char *envp[])
{
	int	outfile;

	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
	{
		perror("outfile");
		exit(EXIT_FAILURE);
	}
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (outfile == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(outfile);
	find_path(argv[3], envp);
}

int	just_one_pipe(t_command *command, char **path)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	child1 = fork();
	if (child1 == -1)
		exit(EXIT_FAILURE);
	if (child1 == 0)
		child_one(fd, command, path);
	// child2 = fork();
	// if (child2 == -1)
	// 	exit(EXIT_FAILURE);
	// if (child2 == 0)
	// 	child_two(fd, command, path);
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(child1, &status, 0);
	// waitpid(child2, &status, 0);
	return (check_status(status))
}

int	pipe_check(t_command *command)
{
	int			total_pipes;
	t_command	*pointer;

	pointer = command;
	total_pipes = 0;
	while (pointer)
	{
		if (pointer->token == PIPE)
			total_pipes++;
		pointer = pointer->next;
	}
	return (total_pipes);
}

int	main(int argc, char **argv, char **envp)
{
	char		*arg;
	char		**path;
	int			i;
	t_command	*command;
	int			total_pipes;

	i = 0;
	(void)argv;
	(void)envp;
	path = get_path(envp);
	// while (path[i])
	// {
	// 	printf("%s\n", path[i]);
	// 	i++;
	// }
	arg = "< infile cat -e | cat -e > text";
	// command = (t_command *)malloc(sizeof(t_command));
	command = NULL;
	init_redirections(arg, &command, path);
	total_pipes = pipe_check(command);
	if (!total_pipes)
	{
		printf("0 pipes");
	}
	else if (total_pipes == 1)
	{
		just_one_pipe(command, path);
	}
}

// void	init_redirections(char *str, t_command **param, char **path)
// {
// 	int			i;
// 	int			x;
// 	int			count;
// 	t_command	*command;

// 	i = 0;
// 	count = 0;
// 	command = *param;
// 	while (str[i])
// 	{
// 		while (str[i] == ' ')
// 			i++;
// 		if (!directions_checker(str, i, 0))
// 			handle_directions(str, i, );
// 		// if (str[i] && (str[i] == '\"' || str[i] == '\''))
// 		// {
// 		// 	command = createnode(&command);
// 		// 	command->arguments = quote_check(str, &i);
// 		// }
// 		i++;
// 	}
// 	printf("command %s\n", command->arguments);
// 	printf("%d\n", count);
// }