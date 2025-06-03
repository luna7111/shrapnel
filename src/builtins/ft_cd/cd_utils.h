#ifndef CD_UTILS_H
# define CD_UTILS_H

void	save_oldpwd(t_data *data, char *oldpwd);
int		handle_chdir(t_data *data, char *target, char *oldpwd);
char	*get_target_path(t_data *data, char **args, int *print_path);
int		cd_error_too_many_args(void);
int		try_cd_fallback(t_data *data);
void	update_pwd_oldpwd(t_data *data, char *oldpwd);

#endif