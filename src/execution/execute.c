
#define ANYPID -1

execute_comand(t_data *data, t_redir *execlist)
{
	char **cmd;
	char **env;

	if (execlist->in_fd != STDIN)
	{
		dup2(execlist->in_fd, STDIN);
		close(execlist->in_fd);
	}
	if (execlist->in_fd != STDOUT)
	{
		dup2(execlist->out_fd, STDOUT);
		close(execlist->out_fd);
	}
	cmd = dup_array(execlist->cmd);//to do
	env = env_to_array(data->env);//to do
	gctrl_cleanup(data->gctrl);
	execve(cmd[0], cmd, );
}

void	execute(t_data *data, t_redir *execlist)
{
	pid_t	pid;
	size_t	process_count;
	
	process_count = 0;
	while (execlist->flag != RE_END)
	{
		if (execlist->flag == RE_OK)
		{
			pid = fork();
			if (pid == 0)
				execute_comand(data, *execlist);
			process_count ++;
			execlist ++;
		}
	}
	while (process_count > 0)
	{
		waitpid(ANYPID);
		process_count--;
	}
}
