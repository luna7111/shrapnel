#include <minishell.h>

#define NO_QUOTES 0
#define SIMPLE_QUOTES 1
#define DOUBLE_QUOTES 2

ptrdiff_t	get_heredoc_len(char *str)
{
	char	*cursor;

	cursor = str + 2;
	while (*cursor == ' ')
		cursor++;
	while (*cursor != ' ' && *cursor != '\0')
	{
		if (*cursor == '"' || *cursor == '\'')
			cursor = ft_strchr(cursor + 1, *cursor);
		else if (*cursor == '<' || *cursor == '>' || *cursor == '|')
			break ;
		cursor ++;
	}
	return (cursor - str);
}

ptrdiff_t	get_token_len(char *str)
{
	char	*cursor;

	cursor = str;
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	else if (!ft_strncmp(str, "<<", 2))
		return (get_heredoc_len(str));
	else if (*str == '<' || *str == '>' || *str == '|')
		return (1);
	while (*cursor != '\0')
	{
		if (*cursor == '"' || *cursor == '\'')
			cursor = ft_strchr(cursor + 1, *cursor);
		else if (*cursor == '<' || *cursor == '>' || *cursor == '|')
			break ;
		cursor ++;
	}
	return (cursor - str);
}

t_pretoken	get_next_token(t_data *data, char *str)
{
	t_pretoken	token;
	char		*raw_piece;
	char		*expanded_piece;

	token.input_len = get_token_len(str);
	raw_piece = ft_substr(str, 0, token.input_len);
	if (*raw_piece == '<' || *raw_piece == '>' || *raw_piece == '|')
		token.type = SIMBOL;
	else
		token.type = TEXT;
	if (token.type == SIMBOL)
		token.str = ft_strtrim(raw_piece, " ");
	else
	{
		expanded_piece = expand_input(data, raw_piece);
		token.str = ft_strtrim(expanded_piece, " ");
		gctrl_free(data->gctrl, expanded_piece);
	}
	token.output_len = ft_strlen(token.str);
	free(raw_piece);
	gctrl_track_ptr(data->gctrl, token.str, LOOP_BLOCK);
	return (token);
}

t_pretoken	*dup_array_size(t_data *data, t_pretoken *original, size_t *size)
{
	t_pretoken	*new;
	size_t		i;

	new = gctrl_malloc(data->gctrl, LOOP_BLOCK, *size * sizeof(t_pretoken) * 2);
	i = 0;
	while (i < *size)
	{
		new[i] = original[i];
		i++;
	}
	gctrl_free(data->gctrl, original);
	*size *= 2;
	return (new);
}

t_pretoken	*pretokenize_input(t_data *data, char *raw_input)
{
	t_pretoken	*token_array;
	t_pretoken	current_token;
	size_t		array_size;
	size_t		i;

	array_size = 8;
	token_array = gctrl_malloc(data->gctrl, LOOP_BLOCK,
			array_size * sizeof(t_pretoken));
	i = 0;
	while (*raw_input != '\0')
	{
		while (*raw_input == ' ')
			raw_input++;
		current_token = get_next_token(data, raw_input);
		token_array[i] = current_token;
		raw_input += current_token.input_len;
		i++;
		if (i >= array_size - 1)
			token_array = dup_array_size(data, token_array, &array_size);
	}
	token_array[i].input_len = 0;
	token_array[i].output_len = 0;
	token_array[i].str = ft_strdup("");
	gctrl_track_ptr(data->gctrl, token_array[i].str, LOOP_BLOCK);
	return (token_array);
}
