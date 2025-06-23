#include "cd_utils.h"
#include <minishell.h>

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

// handles errors, decides where to go and updates the environment.
// oldpwd will save the directory before the change (we use it as OLDPWD)
// target will be the path we want to change.
// printh_path is enabled only if we use cd -
// If more than one argument is passed it shows error.
// Before doing cd,we get the current path and save to oldpwd with getcwd
// Initialize the print_path flag to 0(false).
// call get_target_path to determine where we want to go,cd,cd -,cd path.
// call update_pwd_oldpwd which updates the PWD and OLDPWD in the environment.
// If cd -, it prints the new path(PWD) to stdout, like bash does.