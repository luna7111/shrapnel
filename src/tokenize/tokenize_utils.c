#include <minishell.h>

t_token	*new_node(t_gctrl *gctrl)
{
	t_token	*node;

	node = gctrl_malloc(gctrl, LOOP_BLOCK, sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = NULL;
	node->output_len = 0;
	node->type = -1;
	node->quoted = 0;
	node->next = NULL;
	return (node);
}
// Create a new empty node, with memory from gctrl.
// Initialise all fields of the node(str, len, quoted and next).

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
// Add a t_token node to the end of a linked list.
// If the list is empty, the new node becomes the first one.
// If the list already has elements,
// runs to the end and links the new node...

t_token	*last_node(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
// Used to get the last node in the token list.
// Get the last token created and
// assign it the correct type in get_token_type.

void	unquote_node(t_data *data, t_token *token)
{
	size_t	i;
	size_t	j;
	char	*unquoted;

	unquoted = gctrl_malloc(data->gctrl, LOOP_BLOCK, (token->output_len + 1)
			* sizeof(char));
	i = 0;
	j = 0;
	while (token->str[i] != '\0')
	{
		if (token->str[i] != '"' && token->str[i] != '\'')
		{
			unquoted[j] = token->str[i];
			j++;
		}
		i++;
	}
	unquoted[j] = '\0';
	gctrl_free(data->gctrl, token->str);
	token->str = unquoted;
	token->output_len = ft_strlen(token->str);
}
// Used to remove quotes from the contents of a token.
// Copies each character to the new string except if it is a quote.
// Replaces the original token string with the unquoted version.

void	create_and_add_token(t_data *data, t_token **list, char *str,
		size_t len)
{
	t_token	*node;

	node = new_node(data->gctrl);
	if (!node)
		return ;
	node->str = ft_substr(str, 0, len);
	if (!node->str)
		return ;
	gctrl_track_ptr(data->gctrl, node->str, LOOP_BLOCK);
	node->output_len = ft_strlen(node->str);
	node->type = -1;
	if (ft_strnchr(node->str, '\'', len) || ft_strnchr(node->str, '"', len))
	{
		node->quoted = 1;
		unquote_node(data, node);
	}
	token_add_back(list, node);
}
// Create a node
// Duplicate the string with ft_substr.
// Detect if there are quotes using ft_strnchr.
// If there are quotes, mark quoted = 1 and remove the quotes(unquoted_node).
// Add the node to list with add_back.