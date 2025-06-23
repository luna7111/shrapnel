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

char	*identify_command(t_data *data, char *cmd_name, t_enviroment *path_env)
{
	char	**split_path;
	char	*cmd_path;
	char	*path;
	size_t	i;

	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	if (path_env == NULL)
	{
		printf("Command not found.\n");
		gctrl_cleanup(data->gctrl, ALL_BLOCKS);
		exit (-1);
	}
	path = path_env->content;
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		gctrl_track_ptr(data->gctrl, split_path[i], LOOP_BLOCK);
		split_path[i] = ft_strjoin(split_path[i], "/");
		gctrl_track_ptr(data->gctrl, split_path[i], LOOP_BLOCK);
		split_path[i] = ft_strjoin(split_path[i], cmd_name);
		if (access(split_path[i], X_OK) == 0)
		{
			cmd_path = ft_strdup(split_path[i]);
			free_str_array(split_path);
			return (cmd_path);
		}
		i++;
	}
	free_str_array(split_path);
	printf("Command not found.\n");
	gctrl_cleanup(data->gctrl, ALL_BLOCKS);
	exit(-1);//
}
