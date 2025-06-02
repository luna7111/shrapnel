#include <minishell.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int	ft_cd(t_data *data, char **args)
{
	char	oldpwd[PATH_MAX];    
	char	*target;   
	int		print_path;

	if (args[1] && args[2])
		return (cd_error_too_many_args());

	save_oldpwd(data, oldpwd);
	print_path = 0;
	target = get_target_path(data, args, &print_path);
	if (!target)
		return (1);

	if (handle_chdir(data, target, oldpwd) != 0)
		return (1);

	if (print_path)
		ft_putendl_fd(env_find_node(data->env, "PWD")->content, 1);
	return (0);
}

//Maneja errores, decide a dónde ir y actualiza el entorno.
//oldpwd guardará el directorio antes del cambio(lo usamos como OLDPWD)
//target será la ruta que queremos cambiar.
//printh_path se activa solo si usamos cd -
//Si se pasa más de un argumento muestra error.
//Antes de hacer cd,obtenemos el path actual y lo guardamos en oldpwd con getcwd
//Inicializamos el flag print_path a 0(falso).
//llamamos a get_target_path para determinar donde queremos ir, de, de -, cd ruta.
//llamamos a update_pwd_oldpwd que actualiza el PWD y OLDPWD en el entorno.
//Si es cd -, imprime el nuevo path(PWD) en stdout, como hace bash.

//!!!
//cuando el Working directory se elimina, hay que poder hacer PWD y CD
//si el CD relativo no existe (cd .. cuando el anterior directorio tamoco existe)
//se añade /.. al la ruta, hasta que el directorio sí exista

