#include <minishell.h>
#include "execute.h"

void	set_underscore(t_data *data, t_redir *node)
{
	t_enviroment	*envnode;
	char			*rawvar;
	char			*name;
	size_t			i;

	i = 0;
	while (node->cmd[i + 1] != NULL)
		i++;
	name = node->cmd[i];
	envnode = env_find_node(data->env, "_");
	if (envnode == NULL)
	{
		rawvar = ft_strjoin("_=", name);
		env_add_node(data, rawvar);
		free(rawvar);
	}
	else
	{
		env_set_node(data, "_", name);
	}
}

int	is_builtin(t_redir *exectlist)
{
	char	*name;

	name = exectlist->cmd[0];
	if (!ft_strcmp(name, "cd"))
		return (1);
	if (!ft_strcmp(name, "pwd"))
		return (1);
	if (!ft_strcmp(name, "echo"))
		return (1);
	if (!ft_strcmp(name, "unset"))
		return (1);
	if (!ft_strcmp(name, "export"))
		return (1);
	if (!ft_strcmp(name, "env"))
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (1);
	if (!ft_strcmp(name, "shnake"))
		return (1);
	return (0);
}

int	is_only_builtin(t_redir *execlist)
{
	if (is_builtin(execlist) && execlist[1].flag == RE_END)
		return (1);
	return (0);
}

char	**dup_array(char **original)
{
	char	**array;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (original[size])
		size++;
	array = malloc((size + 1) * sizeof(char *));
	while (i < size)
	{
		array[i] = ft_strdup(original[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**env_to_array(t_enviroment *head)
{
	char	**enviroment;
	size_t	i;

	enviroment = malloc((env_len(head) + 1) * sizeof(char *));
	i = 0;
	while (head)
	{
		enviroment[i] = ft_strdup(head->raw);
		head = head->next;
		i ++;
	}
	enviroment[i] = NULL;
	return (enviroment);
}
