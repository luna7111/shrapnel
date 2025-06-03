#include <errno.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

char	*get_target_path(t_data *data, char **args, int *print_path)
{
	t_enviroment	*var;

	if (!args[1])
	{
		var = env_find_node(data->env, "HOME");
		if (!var || !var->content)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (var->content);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		var = env_find_node(data->env, "OLDPWD");
		if (!var || !var->content)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		*print_path = 1;
		return (var->content);
	}
	if (args[1][0] == '~')
	{
		var = env_find_node(data->env, "HOME");
		if (!var || !var->content)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (ft_strjoin(var->content, args[1] + 1));
	}
	return (args[1]);
}

//Determina a qué directorio cambiar según el argumento cd. cd, cd -, cd path.
//Cuando escribe simplemente cd, sin args, busca la variable HOME.
//Si existe retorna el valor de HOME como destino del cd.
//Cuando el usuario escribe cd -. "volver al directorio anterior".
//Busca la variable OLDPWD en el entorno.
//Activa un flag para indicar que se debe imprimir el nuevo path tras el cambio
//Devuelve el contenido de OLDPWD como path destino.
//Si el argumento empieza con '~'.
//Si $HOME no está definida, se imprime un error.
//Construye una nueva ruta reemplazando ~ por el contenido de $HOME,
//y devolviendo esa ruta combinada.
//finalmente devolvemos el argumento literal, si no hay -, ni ~, ni está vacio.