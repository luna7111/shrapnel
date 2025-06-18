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
				if (tokens->type == INFILE)
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

t_redir	*redirect_tokens(t_data *data, t_token *tokens)
{
	t_redir *array;
	size_t	array_size;
	size_t	i;
	int		pipe[2];

	i = 0;
	pipe[STDIN] = STDIN;
	pipe[STDOUT] = STDOUT;
	array_size = 8;
	array = gctrl_malloc(data->gctrl, LOOP_BLOCK, sizeof(t_redir) * array_size);
	
	while (tokens != NULL)
	{
		array[i].cmd = command_tokens_to_array(data, tokens);
		array[i].fd_in = open_fd_in(data, tokens, pipe[STDIN]);
		open_next_pipe(tokens, pipe);
		array[i].fd_out = open_fd_out(data, tokens, pipe[STDOUT]);
		if (array[i].fd_in == -1 || array[i].fd_out == -1)
			return (NULL);
		while (tokens != NULL && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens != NULL && tokens->type == PIPE)
			tokens = tokens->next;
		i++;
	}
	array[i].cmd = NULL;
	
//	debug, print all redirection nodes;
	i = 0;
	int y = 0;
	while (array[i].cmd != NULL)
	{
		printf("\n--------------\n");
		printf("command:\n\n");
		while (array[i].cmd[y] != NULL)
		{
			printf("%s\n", array[i].cmd[y]);
			y++;
		}
		printf("\n");
		printf("fd in: %d\n", array[i].fd_in);
		printf("fd out: %d\n", array[i].fd_out);
		printf("--------------\n");
		i++;
		y = 0;
	}
	return (NULL);
}
