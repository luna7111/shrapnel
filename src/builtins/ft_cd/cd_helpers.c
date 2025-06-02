#include <minishell.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

void	save_oldpwd(t_data *data, char *oldpwd)
{
	t_enviroment	*pwd;

	if (!getcwd(oldpwd, PATH_MAX))
	{
		pwd = env_find_node(data->env, "PWD");
		if (pwd && pwd->content)
			ft_strlcpy(oldpwd, pwd->content, PATH_MAX);
		else
			oldpwd[0] = '\0';
	}
}
//Nos sirve para guardar el dirct.actual antes de cambiar con cd.
//incluso si el directorio ha sido eliminado.
//Si getcwd falla, si el directorio es borrado porej.
//En es caso usamos la variable $PWD del entorno como ultimo recurso.
//Si no hay nada dejamos string vacía.

static int	try_cd_fallback(t_data *data)
{
	t_enviroment *pwd_var;
	char tmp[PATH_MAX];
	size_t len;

	pwd_var = = env_find_node(data->env, "PWD");
	if (!pwd_var || !pwd_var->content)
		return (1);
	ft_strlcpy(tmp, pwd_var->content, sizeof(tmp));
	len = ft_strlen(tmp);
	while (len > 0)
	{
		ft_strlcat(tmp, "/..", sizeof(tmp));
		if (chdir(tmp) == 0)
			return (0);
		len--;
	}
	return (1);
}
//Si estamos en un direct eliminado y hacemos cd.., 
//esta función intentará construir manualmnte un camino válido
//agregando /.. hasta encontrar un directorio que si exista.


int	handle_chdir(t_data *data, char *target, char *oldpwd)
{
	if (chdir(target) == 0)
	{
		update_pwd_oldpwd(data->env, oldpwd);
		return (0);
	}
	if (ft_strcmp(target, "..") == 0 && try_cd_fallback(data) == 0)
	{
		update_pwd_oldpwd(data->env, oldpwd);
		return (0);
	}
	perror("minishell: cd");
	return (1);
}
//Encapsula el proceso completo de cd incluyendo fallback + actualización.
//Intenta chdir(target).
//Si falla y el target es "..", intenta fallback manual.
//Si alguna funciona, actualiza PWD y OLDPWD.

