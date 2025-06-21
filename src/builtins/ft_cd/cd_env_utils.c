#include <minishell.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

void	update_pwd_oldpwd(t_data *data, char *oldpwd)
{
	char	newpwd[PATH_MAX];

	if (!getcwd(newpwd, sizeof(newpwd)))
	{
		perror("minishell: cd");
		return ;
	}
	env_set_node(data, "OLDPWD", oldpwd);
	env_set_node(data, "PWD", newpwd);
}
//Actualiza las variables PWD y OLDPWD tras hacer cd.
//Creamos un buffer donde guardaremos el nuevo directorio actual(tras chdir).
//Getcwd obtiene el directorio actual del proceso y lo guarda en newpwd. 
//Si getcwd falla mostramos error.
//oldpwd es el directorio en el que estábamos antes de hacer cd.
//Actualizmos OLPWD en mi lista de entorno,con el valor antes del chdir.
//Actualizamos PWD,el path actual,con lo que acabamos de obtener de getcwd.
//Esto refleja correctamente el nuevo directorio tras el c