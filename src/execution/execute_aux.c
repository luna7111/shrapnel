/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   execute_aux.c                                  .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:40:27 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/29 21:59:59 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_str_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	not_found_exit(t_data *data)
{
	printf("Command not found.\n");
	gctrl_terminate(data->gctrl);
	rl_clear_history();
	exit (127);
}

char	*complete_cmdpath(t_data *data, char *split_path, char *cmd_name)
{
	gctrl_track_ptr(data->gctrl, split_path, LOOP_BLOCK);
	split_path = ft_strjoin(split_path, "/");
	gctrl_track_ptr(data->gctrl, split_path, LOOP_BLOCK);
	split_path = ft_strjoin(split_path, cmd_name);
	return (split_path);
}

char	*identify_command(t_data *data, char *cmd_name, t_enviroment *path_env)
{
	char	**split_path;
	char	*cmd_path;
	char	*path;
	size_t	i;

	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	if (path_env == NULL)
		not_found_exit(data);
	path = path_env->content;
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		split_path[i] = complete_cmdpath(data, split_path[i], cmd_name);
		if (access(split_path[i], X_OK) == 0)
		{
			cmd_path = ft_strdup(split_path[i]);
			free_str_array(split_path);
			return (cmd_path);
		}
		i++;
	}
	free_str_array(split_path);
	return (not_found_exit(data), NULL);
}
