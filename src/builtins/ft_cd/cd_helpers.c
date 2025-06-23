#include "cd_utils.h"
#include <minishell.h>

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
// We use it to save the current dirct.current before changing with cd.
// even if the directory has been deleted.
// If getcwd fails, if the directory is deleted byej.
// In this case we use the environment variable $PWD as a last resort.
// If there is nothing we leave empty string.

int	try_cd_fallback(t_data *data)
{
	t_enviroment	*pwd_var;
	char			tmp[PATH_MAX];
	size_t			len;

	pwd_var = env_find_node(data->env, "PWD");
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
// If you are in a deleted direct and cd..,
// this function will try to manually construct a valid path
// by adding /.. until it finds a directory that exists.

int	handle_chdir(t_data *data, char *target, char *oldpwd)
{
	if (chdir(target) == 0)
	{
		update_pwd_oldpwd(data, oldpwd);
		return (0);
	}
	if (ft_strcmp(target, "..") == 0 && try_cd_fallback(data) == 0)
	{
		update_pwd_oldpwd(data, oldpwd);
		return (0);
	}
	perror("minishell: cd");
	return (1);
}
// Encapsulates the entire cd process including fallback + update.
// Try chdir(target).
// If it fails and the target is "...", try manual fallback.
// If either works, update PWD and OLDPWD.