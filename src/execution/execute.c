/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   execute.c                                      .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:40:11 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/30 22:37:05 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "execute.h"

void	clear_next_fds(t_redir *execlist)
{
	execlist++;
	while (execlist->flag != RE_END)
	{
		if (execlist->fd_in > 2)
			close(execlist->fd_in);
		if (execlist->fd_out > 2)
			close(execlist->fd_out);
		execlist++;
	}
}

void	execute_command(t_data *data, t_redir *execlist)
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
	clear_next_fds(execlist);
	if (is_builtin(execlist))
		execute_builtin(data, execlist);
	else
		execute_system_command(data, execlist);
	exit(0);
}

void	pre_execute_command(t_data *data, t_redir *execlist)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	set_underscore(data, execlist);
	pid = fork();
	if (pid == 0)
		execute_command(data, execlist);
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
