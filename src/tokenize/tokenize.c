#include <minishell.h>
#include "tokenize.h"

static size_t	get_word_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

// Calculate length of a token.
// Advance character by character until a ' ' separator is found.
// If a quotation mark is found, advance until the closing character is found.
// Used in extract_token() to find out
// how many characters to extract for a token.

static int	get_token_type(t_token *token, int last_type, int pretoken_type)
{
	if (!token->str)
		return (-1);
	if (!ft_strncmp(token->str, "|", 2) && pretoken_type == SYMBOL)
		return (PIPE);
	if (!ft_strncmp(token->str, "<<", 3) && pretoken_type == SYMBOL)
		return (HEREDOC);
	if (!ft_strncmp(token->str, ">>", 3) && pretoken_type == SYMBOL)
		return (APPEND);
	if (!ft_strncmp(token->str, "<", 2) && pretoken_type == SYMBOL)
		return (INFILE);
	if (!ft_strncmp(token->str, ">", 2) && pretoken_type == SYMBOL)
		return (OUTFILE);
	if (last_type == HEREDOC)
		return (DELIMITER);
	if (last_type == INFILE || last_type == OUTFILE || last_type == APPEND)
		return (FILENAME);
	if (last_type == START || last_type == PIPE)
		return (COMMAND);
	return (COMMAND);
}
// We classify the token type.
// If pretoken_type is SYMBOL and
// the token is |, <<, >>, <, >, classifies it as a symbol.
// If the previous token was redirect or heredoc,
// classifies the next token as DELIMITER or FILENAME.
// If it is the first or comes after |, it marks it as COMMAND.

static void	extract_tokens_from_pretoken(t_data *data, t_token **list,
		t_pretoken *pre)
{
	size_t		i;
	size_t		len;
	static int	last_type = START;

	i = 0;
	len = 0;
	if (pre->type == END)
	{
		last_type = START;
		return ;
	}
	while (pre->str[i])
	{
		while (pre->str[i] == ' ')
			i++;
		if (!pre->str[i])
			break ;
		len = get_word_len(&pre->str[i]);
		create_and_add_token(data, list, &pre->str[i], len);
		last_node(*list)->type = get_token_type(last_node(*list), last_type,
			pre->type);
		last_type = last_node(*list)->type;
		i += len;
	}
}
// Parte un t_pretoken en múltiples t_token reales.
// Recorre pre->str, salta espacios.
// Usa get_word_len() para saber cuánto medir.
// Crea y añade el token con create_and_add_token().
// Clasifica su tipo con get_token_type().

t_token	*tokenize(t_data *data, t_pretoken *input)
{
	t_token	*list;
	size_t	i;

	list = NULL;
	i = 0;
	while (input[i].str != NULL)
	{
		extract_tokens_from_pretoken(data, &list, &input[i]);
		i++;
	}
	extract_tokens_from_pretoken(data, &list, &input[i]);
	return (list);
}
// función principal que recibe el array de t_pretoken y
// devuelve la lista final de t_token.
// Itera cada t_pretoken en input[].
// Llama a extract_tokens_from_pretoken.
// Retorna la lista final.

// FLujo
// tokenize → llama a extract_tokens_from_pretoken

// extract_tokens_from_pretoken → usa get_word_len,
// create_and_add_token, last_node, get_token_type

// create_and_add_token → llama a new_node, token_add_back, unquote_node

// get_word_len y unquote_node → analizan contenido del string, manejan comillas
