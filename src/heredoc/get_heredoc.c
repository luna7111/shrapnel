#include <minishell.h>

static char	*hd_readline(t_gctrl *gctrl)
{
	char	*rawline;
	char	*line;

	rawline = readline("> ");
	line = ft_strjoin(rawline, "\n");
	free (rawline);
	gctrl_track_ptr(gctrl, line, LOOP_BLOCK);
	return (line);
}

char	*get_raw_heredoc(t_data *data, char *delim)
{
	char	*content;
	char	*buf;
	char	*line;

	content = ft_strdup("");
	line = hd_readline(data->gctrl);
	gctrl_track_ptr(data->gctrl, content, LOOP_BLOCK);
	while (ft_strcmp(line, delim) != '\n')
	{
		buf = content;
		content = ft_strjoin(content, line);
		gctrl_track_ptr(data->gctrl, content, LOOP_BLOCK);
		gctrl_free(data->gctrl, line);
		gctrl_free(data->gctrl, buf);
		line = hd_readline(data->gctrl);
	}
	return (content);
}

char	*get_heredoc(t_data *data, t_token *token)
{	
	char	*raw_content;
	char	*content;

	raw_content = get_raw_heredoc(data, token->str);
	if (token->quoted == 1)
		return (raw_content);
	content = expand_heredoc(data, raw_content);
	gctrl_free(data->gctrl, raw_content);
	return (content);
}
