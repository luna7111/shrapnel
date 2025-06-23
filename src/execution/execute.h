#ifndef EXECUTE_H
# define EXECUTE_H

char	*identify_command(t_data *data, char *cmd_name, t_enviroment *path_env);
void	set_underscore(t_data *data, t_redir *node);
int		is_builtin(t_redir *execlist);
int		is_only_builtin(t_redir *execlist);
char	**dup_array(char **original);
char	**env_to_array(t_enviroment *head);
void	free_arrays(char **cmd, char **env);
void	execute_builtin(t_data *data, t_redir *execlist);
void	execute_system_command(t_data *data, t_redir *execlist);
void	execute_command(t_data *data, t_redir *execlist);
void	wait_for_processes(size_t nb);
void	exec_only_builtin(t_data *data, t_redir *execlist);

#endif
