#include <minishell.h>
#define ANYPID -1

char	*identify_command(t_data *data, char *cmd_name, t_enviroment *path_env);

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

void	execute_builtin(t_data *data, t_redir *exectlist)
{
	char	**env;
	char	*name;

	env = env_to_array(data->env);
	name = exectlist->cmd[0];
	if (!ft_strcmp(name, "cd"))
		g_exit_status = ft_cd(data, exectlist->cmd);
	else if (!ft_strcmp(name, "echo"))
		g_exit_status = ft_echo(exectlist->cmd);
	else if (!ft_strcmp(name, "env"))
		g_exit_status = ft_env(env);
	else if (!ft_strcmp(name, "exit"))
		g_exit_status = ft_exit(data, exectlist->cmd);
	else if (!ft_strcmp(name, "export"))
		g_exit_status = ft_export(data, exectlist->cmd);
	else if (!ft_strcmp(name, "pwd"))
		g_exit_status = ft_pwd(data);
	else if (!ft_strcmp(name, "unset"))
		g_exit_status = ft_unset(data, exectlist->cmd);
	else if (!ft_strcmp(name, "shnake"))
		g_exit_status = shnake();
	free_strarray(env);
}

void	execute_system_comand(t_data *data, t_redir *execlist)
{
	char	*cmd_name;
	char	**cmd;
	char	**env;

	cmd = dup_array(execlist->cmd);
	cmd_name = identify_command(data, cmd[0],
			env_find_node(data->env, "PATH"));
	env = env_to_array(data->env);
	gctrl_terminate(data->gctrl);
	signal(SIGINT, SIG_DFL);
	execve(cmd_name, cmd, env);
	data->last_exit_code = errno;
	perror("");
	free_arrays(cmd, env);
}

static void	execute_comand(t_data *data, t_redir *execlist)
{
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
		execute_builtin(data, execlist);
	else
		execute_system_comand(data, execlist);
	exit(0);
}

void	wait_for_processes(size_t nb)
{
	int		wstatus;

	while (nb > 0)
	{
		waitpid(ANYPID, &wstatus, 0);
		g_exit_status = WEXITSTATUS(wstatus);
		nb--;
	}
}

void	exec_only_builtin(t_data *data, t_redir *execlist)
{
	set_underscore(data, execlist);
	execute_builtin(data, execlist);
	if (execlist->fd_in > 2)
		close(execlist->fd_in);
	if (execlist->fd_out > 2)
		close(execlist->fd_out);
}

void	pre_execute_command(t_data *data, t_redir *execlist)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	set_underscore(data, execlist);
	pid = fork();
	if (pid == 0)
		execute_comand(data, execlist);
	if (execlist->fd_in > 2)
		close(execlist->fd_in);
	if (execlist->fd_out > 2)
		close(execlist->fd_out);
}

void	execute(t_data *data, t_redir *execlist)
{
	size_t	process_count;

	process_count = 0;
	if (is_only_builtin(execlist))
		exec_only_builtin(data, execlist);
	else
	{
		while (execlist->flag != RE_END)
		{
			if (execlist->flag == RE_OK)
			{
				pre_execute_command(data, execlist++);
				process_count ++;
			}
			else
			{
				if (execlist->fd_in > 2)
					close(execlist->fd_in);
				if (execlist->fd_out > 2)
					close(execlist->fd_out);
				execlist ++;
			}
		}
	}
	wait_for_processes(process_count);
}
