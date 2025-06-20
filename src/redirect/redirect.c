#include <minishell.h>

size_t	count_cmd_params(t_token *tokens)
{
	size_t	len;

	len = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			len++;
		tokens = tokens->next;
	}
	return (len);
}

char	**command_tokens_to_array(t_data *data, t_token *tokens)
{
	char	**array;
	size_t	cmd_len;
	size_t	i;

	cmd_len = count_cmd_params(tokens);
	array = gctrl_malloc(data->gctrl, LOOP_BLOCK, sizeof(char *) * (cmd_len + 1));
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
		{
			array[i] = ft_strdup(tokens->str);
			gctrl_track_ptr(data->gctrl, array[i], LOOP_BLOCK);
			i++;
		}
		tokens = tokens->next;
	}
	array[i] = NULL;
	return (array);
}

int	open_fd_in(t_data *data, t_token *tokens, int fd)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == INFILE)
		{
			if (tokens->next->type == FILENAME)
			{
				if (fd > 2)
				{
					close(fd);
				}
				fd = open(tokens->next->str, O_RDONLY);
			}
			else
				printf("\n:(\nUncatched error: no filename after infile\n:(\n");
			if (fd == -1)
			{
				perror(tokens->next->str);
				data->last_exit_code = 1;
				return (fd);
			}
		}
		tokens = tokens->next;
	}
	return (fd);
}

int	open_fd_out(t_data *data, t_token *tokens, int fd)
{
	while (tokens && tokens->type != PIPE)	
	{
		if (tokens->type == OUTFILE || tokens->type == APPEND)
		{
			if (tokens->next->type == FILENAME)
			{
				if (fd > 2)
				{
					close(fd);
				}
				if (tokens->type == OUTFILE)
					fd = open(tokens->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else if (tokens->type == APPEND)
					fd = open(tokens->next->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
			}
			else
				printf("\n:(\nUncatched error: no filename after infile\n:(\n");
			if (fd == -1)
			{
				perror(tokens->next->str);
				data->last_exit_code = 1;
				return (fd);
			}
		}
		tokens = tokens->next;
	}
	return (fd);
}

int	open_next_pipe(t_token *tokens, int fildes[2])
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens == NULL)
	{
		fildes[STDOUT] = STDOUT;
		fildes[STDIN] = STDIN;
		return (2);
	}
	return (pipe(fildes));
}

static size_t	duplicate_array(t_data *data, t_redir **array, size_t size)
{
	t_redir	*new_array;
	size_t	i;

	new_array = gctrl_malloc(data->gctrl, LOOP_BLOCK, sizeof(t_redir) * size * 2);
	i = 0;
	while (i < size)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	*array = new_array;
	return (size * 2);
}

t_redir redir_single_node(t_data* data, t_token *tokens, int fd_out, int fd_in)
{
	t_redir node;

	node.cmd = command_tokens_to_array(data, tokens);
	node.fd_in = open_fd_in(data, tokens, fd_in);
	if (node.fd_in == -1)
	{
		node.flag = RE_SKIP;
		return (node);
	}
	node.fd_out = open_fd_out(data, tokens, fd_out);
	if (node.fd_out == -1)
	{
		close(node.fd_in);
		node.flag = RE_SKIP;
	}
	else
		node.flag = RE_OK;
	return (node);
}

t_redir	*redirect_tokens(t_data *data, t_token *tokens)
{
	t_redir *array;
	size_t	array_size;
	size_t	i;
	int		pipe[2];
	int		last_fd;

	i = 0;
	pipe[STDIN] = STDIN;
	pipe[STDOUT] = STDOUT;
	array_size = 8;
	array = gctrl_malloc(data->gctrl, LOOP_BLOCK, sizeof(t_redir) * array_size);
	while (tokens != NULL)
	{
		last_fd = pipe[STDIN];
		open_next_pipe(tokens, pipe);
		array[i] = redir_single_node(data, tokens, pipe[STDOUT], last_fd);
		while (tokens != NULL && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens != NULL && tokens->type == PIPE)
			tokens = tokens->next;
		i++;
		if (i == array_size)
			array_size = duplicate_array(data, &array, array_size);
	}
	array[i].flag = RE_END;
	
//	debug, print all redirection nodes (and close fds);
	i = 0;
	int y = 0;
	while (array[i].flag != RE_END)
	{
		printf("\n--------------\n");
		printf("command:\n\n");
		if (array[i].flag == RE_SKIP)
			printf("(THIS COMMAND WILL NOT BE EXECUTED)\n\n\n");
		while (array[i].cmd[y] != NULL)
		{
			printf("%s\n", array[i].cmd[y]);
			y++;
		}
		printf("\n");
		printf("fd in: %d\n", array[i].fd_in);
		if (array[i].fd_in > 2)
			close(array[i].fd_in);
		printf("fd out: %d\n", array[i].fd_out);
		if (array[i].fd_out > 2)
			close(array[i].fd_out);
		printf("--------------\n");
		i++;
		y = 0;
	}
	return (NULL);
}
