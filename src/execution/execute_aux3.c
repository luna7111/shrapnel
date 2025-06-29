/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   execute_aux3.c                                 .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:40:22 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/29 23:00:20 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "execute.h"
#define ANYPID -1

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

void	execute_system_command(t_data *data, t_redir *execlist)
{
	char	*cmd_name;
	char	**cmd;
	char	**env;

	cmd = dup_array(execlist->cmd);
	cmd_name = identify_command(data, cmd[0],
			env_find_node(data->env, "PATH"));
	env = env_to_array(data->env);
	gctrl_terminate(data->gctrl);
	rl_clear_history();
	signal(SIGINT, SIG_DFL);
	execve(cmd_name, cmd, env);
	g_exit_status = errno;
	perror("");
	free_arrays(cmd, env);
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
	int	buf[2];

	if (execlist->fd_in != STDIN)
		buf[STDIN] = dup(STDIN);
	if (execlist->fd_in != STDIN)
		dup2(execlist->fd_in, STDIN);
	if (execlist->fd_out != STDOUT)
		buf[STDOUT] = dup(STDOUT);
	if (execlist->fd_out != STDOUT)
		dup2(execlist->fd_out, STDOUT);
	set_underscore(data, execlist);
	execute_builtin(data, execlist);
	if (execlist->fd_in > 2)
		close(execlist->fd_in);
	if (execlist->fd_out > 2)
		close(execlist->fd_out);
	if (execlist->fd_in != STDIN)
		dup2(buf[STDIN], STDIN);
	if (execlist->fd_in != STDIN)
		close(buf[STDIN]);
	if (execlist->fd_out != STDOUT)
		dup2(buf[STDOUT], STDOUT);
	if (execlist->fd_out != STDOUT)
		close(buf[STDOUT]);
}
