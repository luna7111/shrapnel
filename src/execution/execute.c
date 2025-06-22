#include <minishell.h>
#define ANYPID -1

char	*identify_command(t_data *data, char *cmd_name, char *path);

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

static char	**dup_array(char **original)
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

static char	**env_to_array(t_enviroment *head)
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

void	free_arrays(char **cmd, char **env)
{
	size_t	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	execute_buiiltin(t_data *data, t_redir *exectlist)
{
	char	**env;
	char	*name;

	env = env_to_array(data->env);
	name = exectlist->cmd[0];
	if (!ft_strcmp(name, "cd"))
		ft_cd(data, exectlist->cmd);
	else if (!ft_strcmp(name, "echo"))
		ft_echo(exectlist->cmd);
	else if (!ft_strcmp(name, "env"))
		ft_env(env);
	else if (!ft_strcmp(name, "exit"))
		ft_exit(data, exectlist->cmd);
	else if (!ft_strcmp(name, "export"))
		ft_export(data, exectlist->cmd);
	else if (!ft_strcmp(name, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(name, "unset"))
		ft_unset(data, exectlist->cmd);
	free_strarray(env);
}

static void	execute_comand(t_data *data, t_redir *execlist)
{
	char	*cmd_name;
	char	**cmd;
	char	**env;

	if (execlist->fd_in != STDIN)
	{
		dup2(execlist->fd_in, STDIN);
		close(execlist->fd_in);
	}
	if (execlist->fd_out != STDOUT)
	{
		dup2(execlist->fd_out, STDOUT);
		close(execlist->fd_out);
	}
	if (is_builtin(execlist))
		execute_buiiltin(data, execlist);
	cmd = dup_array(execlist->cmd);
	cmd_name = identify_command(data, cmd[0],
			env_find_node(data->env, "PATH")->content);
	env = env_to_array(data->env);
	gctrl_terminate(data->gctrl);
	signal(SIGINT, SIG_DFL);
	execve(cmd_name, cmd, env);
	printf("something something command not found\n");
	free_arrays(cmd, env);
	exit(0);
}

void	execute(t_data *data, t_redir *execlist)
{
	pid_t	pid;
	size_t	process_count;

	process_count = 0;
	if (is_only_builtin(execlist))
		execute_buiiltin(data, execlist);
	else
	{
		while (execlist->flag != RE_END)
		{
			if (execlist->flag == RE_OK)
			{
				signal(SIGINT, SIG_IGN);
				pid = fork();
				if (pid == 0)
					execute_comand(data, execlist);
				if (execlist->fd_in > 2)
					close(execlist->fd_in);
				if (execlist->fd_out > 2)
					close(execlist->fd_out);
				process_count ++;
				execlist ++;
			}
		}
	}
	while (process_count > 0)
	{
		waitpid(ANYPID, NULL, 0);
		process_count--;
	}
}
