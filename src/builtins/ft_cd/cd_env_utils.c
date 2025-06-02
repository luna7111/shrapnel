#include <minishell.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

static void	update_pwd_oldpwd(t_enviroment *env, char *oldpwd)
{
	char	newpwd[PATH_MAX];

	if (!getcwd(newpwd, sizeof(newpwd)))
	{
		perror("minishell: cd");
		return ;
	}
	env_set_node(env, "OLDPWD", oldpwd);
	env_set_node(env, "PWD", newpwd);
}
//Actualiza las variables PWD y OLDPWD tras hacer cd.
//Creamos un buffer local donde guardaremos el nuevo directorio actual(tras chdir).
//Getcwd obtiene el directorio actual del proceso y lo guarda en newpwd. 
//Si getcwd falla mostramos error.
//oldpwd es el directorio en el que estábamos antes de hacer cd.
//Actualizamos OLPWD en mi lista de entorno,con el valor que tenía antes del chdir.
//Luego actualizamos PWD,el path actual,con lo que acabamos de obtener de getcwd.
//Esto refleja correctamente el nuevo directorio tras el c