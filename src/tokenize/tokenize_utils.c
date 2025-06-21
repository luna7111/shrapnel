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
// Crea un nuevo nodo vacio, con memoria del gctrl.
// Inicializa todos los campos del nodo(str, len, quoted y next).

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
// Añade un nodo t_token al final de una lista enlazada.
// Si la lista está vacía, el nuevo nodo se convierte en el primero.
// Si la lista ya tiene elementos,
//recorre hasta el final y enlaza el nuevo nodo..

t_token	*last_node(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
// Usada para obtener el último nodo de la lista de tokens.
// Obtenemos el último token creado y
// lo asignamos el tipo correcto en get_token_type.

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
// Usada para eliminiar comillas del contenido de un token.
// Copia cada caracter al nuevo string excepto si es comilla.
// Reemplaza el str original del token con la versión sin comillas.

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
// Creamos un nodo
// Duplicamos el string con ft_substr.
// Detecta si hay comillas usando ft_strnchr.
// Si hay comillas, marca quoted = 1 y elimina las comillas(unquoted_node).
// Añade el nodo a lista con add_back.