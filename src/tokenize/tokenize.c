#include <minishell.h>

static t_token *new_node(t_gctrl *gctrl)
{
	t_token *node;

	node = gctrl_malloc(gctrl, LOOP_BLOCK, sizeof(t_token));
	if(!node)
		return(NULL);
		node->str = NULL;
		node->output_len = 0;
		node->type = -1;
		node->next = NULL;
		return(node);
}
// Crea y devuelve un nuevo nodo t_token vacío.
// La memoria se reserva usando el recolector gctrl.
// Inicializa todos los campos a valores por defecto (NULL, 0, -1)
// y deja el nodo listo para ser rellenado con información.

static void token_add_back(t_token **lst, t_token *new)
{
	t_token *last;

	if(!lst || !new)
		return ;
	if(!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while(last->next)
		last = last->next;
	last->next = new;
}
// Añade un nodo t_token al final de una lista enlazada.
// Si la lista está vacía, el nuevo nodo se convierte en el primero.
// Si la lista ya tiene elementos, recorre hasta el final y enlaza el nuevo nodo..

static int get_token_type(const char *str, int last_type)
{
	if(!str)
		return(-1);
	if(ft_strcmp(str, "|") == 0)
		return(PIPE);
	else if(ft_strcmp(str, "<<") == 0)
		return(HEREDOC);
	else if(ft_strcmp(str, ">>") == 0)
		return(APPEND);
	else if(ft_strcmp(str, ">") == 0)
		return(OUTFILE);
	else if(ft_strcmp(str, "<") == 0)
		return(INFILE);
	else if (last_type == HEREDOC)
		return (DELIMITER);
	else if (last_type == INFILE || last_type == OUTFILE || last_type == APPEND)
		return (FILENAME);
	else
		return (COMMAND);
}
// Determina el tipo de un token en función de su string y del token anterior.
// Reconoce símbolos como pipes o redirecciones, y asigna tipos especiales
// como DELIMITER o FILENAME cuando el contexto lo requiere.
// Si no se detecta ningún caso especial, el token se clasifica como COMMAND.

t_token *tokenize(t_data *data, t_pretoken *input)
{
	t_token	*list;
	t_token	*node;
	size_t	i;
	int		last_type;

	list = NULL;
	last_type = START;
	i = 0;
	while (input[i].str != NULL)
	{
		node = new_node(data->gctrl);
		if (!node)
			return (NULL);
		node->str = ft_strdup(input[i].str);
		if (!node->str)
			return (NULL);
		gctrl_track_ptr(data->gctrl, node->str, LOOP_BLOCK);
		node->output_len = input[i].output_len;
		node->type = get_token_type(node->str, last_type);
		last_type = node->type;

		token_add_back(&list, node);
		i++;
	}
	return (list);
}
// Función principal del proceso de tokenización.
// Recorre un array de pretokens (resultado del pretokenize),
// y construye una lista enlazada de tokens (t_token).
// Para cada entrada, reserva memoria, copia el contenido,
// determina su tipo en base al contexto anterior (redirecciones, delimitadores, etc.)
// y lo añade al final de la lista.