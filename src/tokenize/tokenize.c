#include <minishell.h>


static size_t get_word_len(char *str)
{
    size_t i = 0;

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

//Calcula longitud de un token
//Avanza caracter a caracter hasta encontrar un separador ' '.
//Si encuentra una comilla avanza hasta encontrar el cierre.
//Usada en extract_token.. para saber cuantos caracteres extraer para un token.

t_token *new_node(t_gctrl *gctrl)
{
    t_token *node;

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
//Crea un nuevo nodo vacio, con memoria del gctrl.
//Inicializa todos los campos del nodo(str, len, quoted y next).

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

static t_token *last_node(t_token *lst)
{
    while (lst && lst->next)
        lst = lst->next;
    return (lst);
}
//Usada para obtener el último nodo de la lista de tokens.
//Obtenemos el último token creado y 
//lo asignamos el tipo correcto en get_token_type.

static void unquote_node(t_data *data, t_token *token)
{
    size_t  i;
    size_t  j;
    char    *unquoted;

    unquoted = gctrl_malloc(data->gctrl, LOOP_BLOCK, (token->output_len + 1) * sizeof(char));

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
//Usada para eliminiar comillas del contenido de un token.
//Copia cada caracter al nuevo string excepto si es comilla.
//Reemplaza el str original del token con la versión sin comillas.

static void create_and_add_token(t_data *data, t_token **list, char *str, size_t len)
{
    t_token *node = new_node(data->gctrl);
    if (!node)
        return ;
    node->str = ft_substr(str, 0, len);
    if (!node->str)
        return ;
    gctrl_track_ptr(data->gctrl, node->str, LOOP_BLOCK);
    node->output_len = ft_strlen(node->str);
    node->type = -1;
    if(ft_strnchr(node->str, '\'', len) || ft_strnchr(node->str, '"', len))
    {
        node->quoted = 1;
        unquote_node(data, node);
    }
    token_add_back(list, node);
}
//Creamos un nodo
//Duplicamos el string con ft_substr.
//Detecta si hay comillas usando ft_strnchr.
//Si hay comillas, marca quoted = 1 y elimina las comillas(unquoted_node).
//Añade el nodo a lista con add_back.

int get_token_type(t_token *token, int last_type, int pretoken_type)
{
    if (!token->str)
        return (-1);
    if (!ft_strncmp(token->str, "|", 2) && pretoken_type == SYMBOL)
        return PIPE;
    if(!ft_strncmp(token->str, "<<", 3) && pretoken_type == SYMBOL)
        return HEREDOC;
    if(!ft_strncmp(token->str, ">>", 3) && pretoken_type == SYMBOL)
        return APPEND;
    if(!ft_strncmp(token->str, "<", 2) && pretoken_type == SYMBOL)
        return INFILE;
    if(!ft_strncmp(token->str, ">", 2) && pretoken_type == SYMBOL)      
        return OUTFILE;
    if(last_type == HEREDOC)
        return DELIMITER;
    if(last_type == INFILE || last_type == OUTFILE || last_type == APPEND)
        return FILENAME;
    if(last_type == START || last_type == PIPE)
        return COMMAND;
    return COMMAND;
}
//Clasificamos el tipo de token.
//Si pretoken_type es SYMBOL y 
//el token es |, <<, >>, <, >, lo clasifica como símbolo.
//Si el token anterior era redirección o heredoc, 
//clasifica el siguiente como DELIMITER o FILENAME.
//Si es el primero o viene tras |, lo marca como COMMAND.

static void extract_tokens_from_pretoken(t_data *data, t_token **list, t_pretoken *pre)
{
    size_t i = 0;
    size_t len = 0;
    int    quoted;
    int     last_type = START;

    while (pre->str[i])
    {
        quoted = 0;
        while (pre->str[i] == ' ')
            i++;
        if (!pre->str[i])
            break;
        len = get_word_len(&pre->str[i]);
        if (ft_strnchr(&pre->str[i], '\'', len) || ft_strnchr(&pre->str[i], '"', len))
            quoted = 1;
        create_and_add_token(data, list, &pre->str[i], len);
        last_node(*list)->type = get_token_type(last_node(*list), last_type, pre->type);
        i += len;
    }
}
//Parte un t_pretoken en múltiples t_token reales.
//Recorre pre->str, salta espacios.
//Usa get_word_len() para saber cuánto medir.
//Crea y añade el token con create_and_add_token().
//Clasifica su tipo con get_token_type().

t_token *tokenize(t_data *data, t_pretoken *input)
{
    t_token *list = NULL;
    //int last_type = START;
    size_t i = 0;

    while (input[i].str != NULL)
    {
        extract_tokens_from_pretoken(data, &list, &input[i]);
        i++;
    }
    return (list);
}
//función principal que recibe el array de t_pretoken y 
//devuelve la lista final de t_token.
//Itera cada t_pretoken en input[].
//Llama a extract_tokens_from_pretoken.
//Retorna la lista final.

//FLujo
//tokenize → llama a extract_tokens_from_pretoken

//extract_tokens_from_pretoken → usa get_word_len, 
//create_and_add_token, last_node, get_token_type

//create_and_add_token → llama a new_node, token_add_back, unquote_node

//get_word_len y unquote_node → analizan contenido del string, manejan comillas