/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   cd_target.c                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:36:58 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:36:58 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "cd_utils.h"

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

// Determines which directory to change to based on the cd argument. 
// cd, cd -,cd path.
// When simply typing cd, without args, looks for the variable HOME.
// If it exists, returns the value of HOME as the destination of cd.
// When the user types cd -. "return to previous directory".
// Find the OLDPWD variable in the environment.
// Activates a flag to indicate that the new path should be 
// printed after the change
// Returns the contents of OLDPWD as the destination path.
// If the argument starts with '~'.
// If $HOME is not defined, an error is printed.
// Constructs a new path by replacing ~ with the contents of $HOME,
// and returning that combined path.
// Finally we return the literal argument, if there is no -, nor ~,
// nor is it empty.
