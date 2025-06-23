/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   redirect_aux.c                                 .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:38:10 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:38:11 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

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
	array = gctrl_malloc(data->gctrl, LOOP_BLOCK,
			sizeof(char *) * (cmd_len + 1));
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

int	open_heredoc(t_data *data, t_token *tokens)
{
	char	*hdoc_content;
	int		pipe_fd[2];

	pipe(pipe_fd);
	hdoc_content = get_heredoc(data, tokens->next);
	write(pipe_fd[STDOUT], hdoc_content, ft_strlen(hdoc_content));
	close(pipe_fd[STDOUT]);
	return (pipe_fd[STDIN]);
}

int	open_fd_in(t_data *data, t_token *tokens, int fd)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == HEREDOC)
		{
			if (fd > 2)
				close(fd);
			fd = open_heredoc(data, tokens);
		}
		else if (tokens->type == INFILE)
		{
			if (fd > 2)
				close(fd);
			fd = open(tokens->next->str, O_RDONLY);
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
					close(fd);
				if (tokens->type == OUTFILE)
					fd = open(tokens->next->str,
							O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else if (tokens->type == APPEND)
					fd = open(tokens->next->str,
							O_WRONLY | O_CREAT | O_APPEND, 0666);
			}
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
