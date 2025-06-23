/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   ft_pwd.c                                       .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:36:15 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:36:18 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
// Receives the main struct t_data containing the environment list env.
// Declares a buffer with maximum allowed path size. 
// Saves the path from the current direct.
// calls getcwd to get the current path. if perror fails.
// prints the current path to standard output (fd 1) and adds "PWD".
// Find in your environment linked list the variable "PWD" using your function
// env_find_node.
// If the variable PWD exists in the environment list. Start the block for
// update PWD.
// Release the previous contents of PWD.
// Copy the new path to the content field of the PWD variable.
