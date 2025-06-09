#include <minishell.h>

#define NO_QUOTES 0
#define SIMPLE_QUOTES 1
#define DOUBLE_QUOTES 2

static ptrdiff_t	get_heredoc_len(char *str)
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

static ptrdiff_t	get_token_len(char *str)
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

static t_pretoken	get_next_token(t_data *data, char *str)
{
	t_pretoken	token;
	char		*raw_piece;
	char		*expanded_piece;

	token.input_len = get_token_len(str);
	raw_piece = ft_substr(str, 0, token.input_len);
	if (*raw_piece == '<' || *raw_piece == '>' || *raw_piece == '|')
		token.type = SYMBOL;
	else
		token.type = TEXT;
	if (token.type == SYMBOL)
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

static t_pretoken	*dup_array_len(t_data *data, t_pretoken *prev, size_t *len)
{
	t_pretoken	*new;
	size_t		i;

	new = gctrl_malloc(data->gctrl, LOOP_BLOCK, *len * sizeof(t_pretoken) * 2);
	i = 0;
	while (i < *len)
	{
		new[i] = prev[i];
		i++;
	}
	gctrl_free(data->gctrl, prev);
	*len *= 2;
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
			token_array = dup_array_len(data, token_array, &array_size);
	}
	token_array[i].input_len = 0;
	token_array[i].output_len = 0;
	token_array[i].str = NULL;
	token_array[i].type = END;
	return (token_array);
}
// The function takes a string (such as "cat << end | wc -l > $FILE")
// and divides it into tokens, this step is necessary to prevent literal
// characters to be identified as redirection symbols further in the tokening
// process.
//
// Ej:
// Given an env variable "$PIPE" containing the string "|", the input
// "echo hello world $PIPE cat -e" would print "hello world | cat -e" as a
// literal string.
//
// Expansion has to happen before the main tokening because a variable can
// expand to a valid command, which should execute.
//
// Pretokens are structs arranged in an array. They contain the following
// members:
//
// char* str         -> the pretoken string.
// size_t input_len  -> the length the pretoken occupies in the original
//                      string, for example $FILE would expand to filename.txt
//                      but the input_len whould be set to 5, bc that's how
//                      long the original string was.
// size_t output_len -> the length of the string contained by the pretoken
//                      in the previous example, it would be 12 bc that's how
//                      much filename.txt occupies.
// int type          -> this is the type of the pretoken. TEXT (1) SYMBOL (2)
//                      and END (0). 
//
// The first example would be pretokenized as such:
//
// ---
// "cat"
// 4
// 3
// TEXT
// ---
// "<< end"
// 6
// 6
// SYMBOL
// ---
// "|"
// 1
// 1
// SYMBOL
// ---
// "wc -l"
// 6
// 5
// TEXT
// ---
// ">"
// 1
// 1
// SYMBOL
// ---
// "filename.txt"
// 5 
// 12
// TEXT
// ---
// (null)
// 0
// 0
// END
