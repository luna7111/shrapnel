#include <minishell.h>


static size_t get_word_len(char *str)
{
    size_t i = 0;

    while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '|')
        i++;
    return (i);
}
//devuelve el nº de carcteres hasta el siguiente separador.
//(espacio, '<', '>', '|'), ignorando comillas.
//se usa para calcular la longitud de una palabra sin simbolos.
//la usamos en extract_token, para saber hasta donde extraer
//texto continuo sin separadores.
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

static void create_and_add_token(t_data *data, t_token **list, char *str, size_t len, int quoted)
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
    node->quoted = quoted;
    token_add_back(list, node);
}
//Reserva y construye un t_token con la subcadena extraida.
//le asigna longitud, el flag quoted(1 o 0) y añade a la lista.
//Le asigna el str con ft_substr(), output_len, y la flag quoted.
// Flag para saber si el token estaba entre comillas.
//Es llamada por extract_tokens_from_pretoken() para generar cada token real.

static void extract_tokens_from_pretoken(t_data *data, t_token **list, char *str)
{
    size_t i = 0;
    size_t len;
    int quoted;

    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (!str[i])
            break;

        quoted = (str[i] == '"' || str[i] == '\'');
        if (quoted)
        {
            char quote = str[i++];
            len = 0;
            while (str[i + len] && str[i + len] != quote)
                len++;
            create_and_add_token(data, list, &str[i], len, 1);
            i += len;
            if (str[i] == quote)
                i++; // saltar la comilla de cierre
        }
        else
        {
            if (!ft_strncmp(&str[i], "<<", 2) || !ft_strncmp(&str[i], ">>", 2))
                len = 2;
            else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
                len = 1;
            else
                len = get_word_len(&str[i]);

            create_and_add_token(data, list, &str[i], len, 0);
            i += len;
        }
    }
}


//Recibe un pretoken y lo parte en varios t_token.
//Reconoce comillas (" o ') y simbolos como <<, >>, |, etc.
//Marca la flag quoted si el token venía con comillas.
// Se llama una vez por cada t_pretoken dentro de tokenize.

int get_token_type(char *str, int last_type)
{
    if (!str)
        return -1;
    if (!ft_strncmp(str, "|", 2))
        return PIPE;
    if (!ft_strncmp(str, "<<", 3))
        return HEREDOC;
    if (!ft_strncmp(str, ">>", 3))
        return APPEND;
    if (!ft_strncmp(str, "<", 2))
        return INFILE;
    if (!ft_strncmp(str, ">", 2))
        return OUTFILE;
    if (last_type == HEREDOC)
        return DELIMITER;
    if (last_type == INFILE || last_type == OUTFILE || last_type == APPEND)
        return FILENAME;
    if (last_type == START || last_type == PIPE)
        return COMMAND;
    return COMMAND; // Por defecto
}
//Clasifica un token según su contenido (<, >>, etc.) 
//y el contexto anterior (last_type).
//Si viene después de un <<, lo marca como DELIMITER.
//Si viene después de un >, lo marca como FILENAME, etc.


t_token *tokenize(t_data *data, t_pretoken *input)
{
    t_token *list;
    int last_type;
    size_t i;
    t_token *curr;

	list = NULL;
	last_type = START;
	i = 0;
	curr = NULL;
    while (input[i].str != NULL)
    {
        extract_tokens_from_pretoken(data, &list, input[i].str);
        i++;
    }

    curr = list;
    while (curr)
    {
        curr->type = get_token_type(curr->str, last_type);
        last_type = curr->type;
        curr = curr->next;
    }
    return (list);
}
//Función principal
//Recorre los pretokens, los trocea con extract_tokens_from_pretoken, 
//y genera la lista final de t_token.
//llama a get_token_type para asignar el tipo correcto (PIPE, DELIMITER, etc.).




//primer dividir el str en tokens sin tener en cuenta las comillas (en cuanto al len)
//ir iterando por cada nodo del pretoken, y dentro de cada nodo separar por cada palabra
//usar substring en vez de strdup
//funcion extra, de longitud del token.
//luego hacer el substring en otra funcion
//crearme una lista con los tokens de cada pretoken y luego añadirñlas con addback
//tenemos que tener en cuenta esto: cat <<end es valido, y tiene que separar << de end.
