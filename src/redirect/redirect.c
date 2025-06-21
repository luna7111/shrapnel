#include <minishell.h>
#include "redirect.h"

static int	open_next_pipe(t_token *tokens, int fildes[2])
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

	new_array = gctrl_malloc(data->gctrl,
			LOOP_BLOCK, sizeof(t_redir) * size * 2);
	i = 0;
	while (i < size)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	*array = new_array;
	return (size * 2);
}

static t_redir	redir_node(t_data *data, t_token *tokens, int fd_out, int fd_in)
{
	t_redir	node;

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
	t_redir	*array;
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
		array[i] = redir_node(data, tokens, pipe[STDOUT], last_fd);
		while (tokens != NULL && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens != NULL && tokens->type == PIPE)
			tokens = tokens->next;
		if (i++ == array_size)
			array_size = duplicate_array(data, &array, array_size);
	}
	array[i].flag = RE_END;
	return (array);
}
