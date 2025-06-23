#include <minishell.h>
#include <limits.h> 

int	ft_pwd(t_data *data)
{
	char			path[PATH_MAX];
	t_enviroment	*pwd_node;

	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	pwd_node = env_find_node(data->env, "PWD");
	if (pwd_node)
	{
		gctrl_free(data->gctrl, pwd_node->content);
		pwd_node->content = ft_strdup(path);
		gctrl_track_ptr(data->gctrl, pwd_node->content, PROG_BLOCK);
	}
	return (0);
}
//Recibe el struct principal t_data que contiene la lista de entorno env.
//Declara un buffer con tamaño máximo del path permitido. Se guarda el path del
//direct. actual.
//llama a getcwd para obtener el path actual. si falla perror.
//imprime el path actual en la salida estándar (fd 1) y añade "\n".
//Busca en tu lista enlazada de entorno la variable "PWD" usando tu función
//env_find_node.
//Si la variable PWD existe en la lista de entorno. Comienza el bloque para
//actualizar PWD.
// Libera el contenido anterior de PWD.
//Copia el nuevo path al campo content de la variable PWD.
