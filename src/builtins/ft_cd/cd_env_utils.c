#include <minishell.h>
#include "cd_utils.h"

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
// Update PWD and OLDPWD variables after cd.
// Create a buffer to store the new current directory (after chdir).
// Getcwd gets the current directory from the process and stores it in newpwd.
// If getcwd fails, we show error.
// oldpwd is the directory we were in before cd.
// Update OLPWD in my environment list,with the value before chdir.
// Update PWD,the current path,with what we just got from getcwd.
